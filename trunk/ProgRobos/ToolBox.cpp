#include "ToolBox.h"

namespace ToolBox {

    /**
     * Preenche a matriz de visão do Robô.
     * @param pRobot ponteiro para o Robô
     * @param matrix referência para a matriz que deve ser povoada
     * @param deteccao true: modo de detecção inicial onde o robô "enxerga pouco". 
     * false: detecção usual, onde o Robô leva em consideração tudo o que vê, e
     * não só uma caixinha virtual pequena a sua frente.
     */
    void FillVisionMatrix(Robot *pRobot, Matrix& matrix, bool deteccao) {
        int col = 0, row = 0; //x e y estão em unidades de caixas
        double rangeX, rangeY; //unidade: metros
        double rangeX_max, rangeY_max, rangeY_min; //unidade: metros
        int nfives = 0; //contador pra checar o tamanho do Prof.

        matrix.Clean();

        /* seta os limites da visão do robô. Se for detecção, enxerga
         * um retângulo pequeno, caso contrário tem visão total. */
        if (deteccao) {
            pRobot->SetProfSizeOnMatrix(0); //zera tamanho do Prof na matriz, pois será recalculado
            rangeX_max = DETECTIONBOX_WIDTH / 2.0;
            rangeY_max = DETECTIONBOX_LENGTH;
            rangeY_min = 0;
        } else {
            rangeX_max = MAXRANGE;
            rangeY_max = MAXRANGE;
            rangeY_min = -MAXRANGE;
        }

        /* leio todos os lasers */
        for (int i = LASER_FIRST; i <= LASER_LAST; i++) {
            double Range = pRobot->GetRange(i);

            /* descarto leituras fora de MINRANGE e MAXRANGE, caso o Hokuyo responda algum valor inválido */
            if (Range < MINRANGE || Range > MAXRANGE)
                continue;

            rangeX = Range * cos(RADIAN(i));
            rangeY = Range * sin(RADIAN(i));
            col = (int) (BOXES_COLUMNS / 2) + floor(rangeX / BOXSIZE);
            row = (int) (BOXES_ROWS / 2) - floor(rangeY / BOXSIZE);

            /* limitando a visão do robô, caso escolhido 'deteccao=true' */
            if (rangeY < 0) {
                if (fabs(rangeX) > rangeX_max || rangeY < rangeY_min)
                    continue;
            } else {
                if (fabs(rangeX) > rangeX_max || rangeY > rangeY_max)
                    continue;
            }

            /* todos os pontos que chegaram até aqui serão detectados,
             * pois fazem parte do que deve ser enxergado pelo robô */

            if (deteccao) { //marca tudo com 5
                if (matrix.get(row, col) != 5) {
                    matrix(row, col) = 5;
                    pRobot->IncreaseProfSizeOnMatrix();
                }
            } else { //marca com -1 e compara com as 2 visões (atual e anterior) pra decidir se é o Prof ou não
                if (matrix.get(row, col) == 5) //se for um 5 já detectado, não faz nada
                    continue;
                else { //verifica se este ponto será um 5 ou um -1
                    if ((isNextToFives(pRobot->GetPreviousVisionMatrix(), row, col) ||
                            isNextToFives(pRobot->GetVisionMatrix(), row, col)) &&
                            nfives < pRobot->GetProfSizeOnMatrix()) {//se estiver perto de outros 5's, é 5.
                        matrix(row, col) = 5;
                        nfives++;
                    } else //se não estiver perto de outros 5's, é -1
                        matrix(row, col) = -1;
                }
            }
        }
        PRINT(GetNumberOfFives(matrix));
        PRINT(pRobot->GetProfSizeOnMatrix());
        //        matrix.Print();
        //        cout << endl;
        //ShowVisionMatrix(pRobot->GetCurrentVisionMatrix()) //versão de matrix.Print() só que em OpenCV
    }

    /**
     * Percorre a matriz de visão procurando se tem algum 5 ao redor do elemento row,col
     * @param matrix matriz onde deve ser feita a procura. Pode ser a visão anterior ou atual do robô
     * @param row linha do elemento
     * @param col coluna do elemento
     * @return true se tem 5 ao redor do elemento row,col; false caso contrário
     */
    bool isNextToFives(Matrix& matrix, int row, int col) {
        for (int k = -1; k <= 1; k++)
            for (int l = -1; l <= 1; l++) {
                if (row + k >= 1 && row + k <= matrix.GetRows() && col + l >= 1 && col + l <= matrix.GetCols())
                    if (matrix.get(row + k, col + l) == 5)
                        return true;
            }
        return false;
    }

    /**
     * Retorna o número de cincos presente numa matriz de visão
     * @param matrix matriz de visão
     * @return número de cincos na matriz de visão
     */
    int GetNumberOfFives(Matrix& matrix) {
        int num = 0;

        for (int i = 1; i <= matrix.GetRows(); i++)
            for (int j = 1; j <= matrix.GetCols(); j++)
                if (matrix.get(i, j) == 5)
                    num++;
        return num;
    }

    /**
     * Retorna a distância em metros do Prof ao robô na matriz de visão
     * @param matrix matriz onde devem ser feitos os cálculos
     * @return a distância entre o robô e o Professor, em metros.
     */
    double GetProfDistance(Matrix& matrix) {
        Point<int> PCentro(0, 0);
        Point<int> CMOfFives = GetCMOfFives(matrix, REFERENCIAL_ROBOT);

        return (Point<int>::GetDistance(PCentro, CMOfFives) * BOXSIZE);
    }

    /**
     * Retorna o centro de massa dos 5's da matriz (representação do Professor), com a
     * referência podendo ser, ou no começo da matriz (posição (1,1)), ou no centro da
     * matriz (visão do Robô).
     * @param matrix matriz de visão do robô
     * @param ref indica se é pra retornar o ponto com relação ao referencial Global
     * REFERENCIAL_MATRIX, ou ao referencial local do Robô (referencial centrado na matriz)
     * @return centro de massa dos 5's na matriz (CM do Professor)
     */
    Point<int> GetCMOfFives(Matrix& matrix, Referencial ref) {
        list< Point<int> > LP;
        list< Point<int> >::iterator it;
        Point<int> res(0, 0);
        Point<int> CenterVM((int) (BOXES_ROWS / 2), (int) (BOXES_COLUMNS / 2)); //VisionMatrix center

        for (int row = 1; row <= matrix.GetRows(); row++)
            for (int col = 1; col <= matrix.GetCols(); col++)
                if (matrix.get(row, col) == 5)
                    LP.push_back(*(new Point<int>(row, col)));

        /* se não houver 5's na matriz de visão, significa que o Prof não foi
         detectado. Retorna (0,0) indicando isso. */
        if (LP.size() == 0)
            return *(new Point<int>(0, 0));

        for (it = LP.begin(); it != LP.end(); it++)
            res += *it;

        res /= LP.size();

        /* limpa a memória */
        LP.clear();

        switch (ref) {
            case REFERENCIAL_MATRIX:
                return res;
                break;
            case REFERENCIAL_ROBOT:
                Point<int> P(CenterVM.GetX() - res.GetX(), res.GetY() - CenterVM.GetY());
                return P;
        }

        //não é pra chegar aqui. Se chegar, deu erro.
        exit(-1);
        return *(new Point<int>(-1, -1));
    }
}