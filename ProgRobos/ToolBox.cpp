#include "ToolBox.h"

namespace ToolBox {

    /**
     * Preenche a matriz de visão do Robô.
     * @param pRobot ponteiro para o Robô
     * @param matrix referência para a matriz que deve ser povoada
     * @param deteccao true: modo de detecção inicial, onde o robô "enxerga pouco". 
     * false: detecção usual, onde o Robô leva em consideração tudo o que vê, e não
     * só uma caixinha virtual pequena a sua frente.
     */
    void FillVisionMatrix(Robot *pRobot, Matrix& matrix, bool deteccao) {
        int col = 0, row = 0; //x e y estão em unidades de caixas
        double rangeX, rangeY; //unidade: metros
        double rangeX_max, rangeY_max, rangeY_min; //unidade: metros
        int nfives = 0; //contador pra checar o tamanho do Prof.
        Point<int> P; //ponto contendo as coordenadas da linha (row) e coluna (col) da matriz de visão
        list < Point<int> > PointList; //lista de pontos
        list < Point<int> >::iterator iterador; //iterador pra lista de pontos

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

            rangeX = Range * cos(ANGLERADIAN(i));
            rangeY = Range * sin(ANGLERADIAN(i));

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

            col = (int) (BOXES_COLUMNS / 2) + floor(rangeX / BOXSIZE);
            row = (int) (BOXES_LINES / 2) + floor(rangeY / BOXSIZE);
            P.Set(row, col);

            if (deteccao) { //marca tudo com 5
                if (matrix.get(row, col) != 5) {
                    matrix(row, col) = 5;
                    pRobot->IncreaseProfSizeOnMatrix();
                }
            } else { //marca com -1 e compara com as 2 visões (atual e anterior) pra decidir se é o Prof ou não
                PointList.push_back(P); //append o novo ponto na lista
                PointList.unique(); //remove elementos duplicados da lista
                matrix(row, col) = -1;
                if ((isNextToFives(pRobot->GetPreviousVisionMatrix(), row, col) || \
                     isNextToFives(pRobot->GetCurrentVisionMatrix(), row, col)) && \
                     nfives <= pRobot->GetProfSizeOnMatrix() + 2) {
                    matrix(row, col) = 5;
                    iterador = find(PointList.begin(), PointList.end(), P);
                    if (*iterador == P)
                        nfives++;
                }
            }
        }
        PointList.clear(); //limpa a lista (desaloca memória)
        PRINT(GetNumberOfFives(matrix));
        PRINT(pRobot->GetProfSizeOnMatrix());
        cout << endl;
        //        matrix.Print();
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
        return 3.0;
    }
}
