#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include "ToolBox.h"
#include <cmath>

using namespace std;

void S_Tracking::Enter(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nEntrando no S_Tracking" << endl;
#endif
}

void S_Tracking::Execute(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nExecutando a S_Tracking" << endl;
#endif
    /* Utilizamos 1.1m como distância ideal Prof<-->robô. Qualquer variação de
     * 10cm dessa distância, fará o robô tentar voltar para a distância ideal
     * de 1.1m. Seja 'dist' a variável que mede o desvio da distância ideal.
     * Distinguimos 5 faixas de distâncias onde o robô tomará diferentes decisões,
     * porém permanecerá neste estado. São elas:
     * 
     * 1) Entre 0 e 0.5m do robô:
     *    O robô ficará parado: XSpeed = YawSpeed = 0. Assumimos isso pois possivelmente
     *    é a situação em que o Prof tentará pegar o robô e, portanto, o robô não
     *    deverá fugir.
     * 
     * 2) Entre 0.5 e 1m do robô:
     *    O robô se afastará com velocidade proporcional à proximidade. Quanto mais
     *    próximo, maior a velocidade para trás.
     *    -0.2 <= XSpeed < 0; YawSpeed é livre
     * 
     * 3) Entre 1 e 1.2m do robô:
     *    Essa é a distância ideal. Não nos aproximamos do Prof nessa distância,
     *    mas tentamos manter a visada: mantemos o robô olhando para o Prof.
     *    XSpeed = 0; YawSpeed é livre
     * 
     * 4) Entre 1.2 e 3.95m (MAXRANGE) do robô:
     *    O robô se aproximará do Prof com velocidade proporcional ao afastamento.
     *    Quando mais afastado, maior a velocidade. A máxima velocidade (0.2m/s)
     *    será quando o afastamento for 2m. De 2 a 3.95m a velocidade permanecerá
     *    constante em 0.2m/s.
     *    0 < XSpeed <= 0.2; YawSpeed é livre
     * 
     * 5) Acima de 3.95m do robô:
     *    O robô perdeu o rastro. Fazemos XSpeed = YawSpeed = 0 e mudamos para o
     *    estado 'S_LostTrack'
     * 
     * 
     * Separamos o tratamento do desvio angular em duas situações:
     * 
     * 1) Desvio angular entre -5 e 5 graus:
     *    Não faremos o robô girar (olhar para o Prof), para não estressar os motores.
     *    Achamos que, como há ruído, se tentássemos corrigir todo desvio, mesmo
     *    com o Prof parado haveria ruído e os motores seriam acionados. Por isso
     *    decidimos dar esta "folga" de 10 graus para o CM (centro de massa) poder
     *    "dançar" um pouco em frente do robô.
     *    YawSpeed = 0
     * 
     * 2) Desvios fora da faixa -10 e 10 graus:
     *    São todos corrigidos com velocidade de giro proporcionais ao desvio.
     */

    Point<int> CMProf = ToolBox::GetCMOfFives(pRobot->GetVisionMatrix(), REFERENCIAL_ROBOT);
    double ProfDist = CMProf.module() * BOXSIZE; //não usei ToolBox::GetProfDistance por questões de performance
    double dist = ProfDist - DETECTION_DISTANCE; //desvio da distância ideal
    double DesvioAngular = -CMProf.argument(); //desvio angular entre o robô e o Professor
    double XSpeed = 0; //velocidade para frente
    double YawSpeed = 0; //velocidade de giro


    /* se perdeu rastro, vai para o estado S_LostTrack */
    if (ProfDist > MAXRANGE || CMProf.equals(0, 0))
        pRobot->GetFSM()->ChangeToState(S_LostTrack::Instance());

    /* tratamento do desvio angular:
     * - desvios entre -1 e 10 graus: não faz nada.
     * - caso contrário, corrige proporcionalmente ao desvio */
    if (abs(DesvioAngular) > DTOR(10))
        YawSpeed = DesvioAngular;

    
    /* tratamento da distância */

    //se MUITO perto, fica parado.
    if (ProfDist <= 0.5) {
        XSpeed = 0;
        YawSpeed = 0;
    }

    //se perto, afasta
    if (ProfDist > 0.5 && ProfDist < DETECTION_DISTANCE - 0.1)
        XSpeed = 0.8 * dist;

    //se longe, persegue
    if (ProfDist > DETECTION_DISTANCE + 0.1)
        XSpeed = 0.02 + 0.2 * dist;

#ifdef DEBUG
    PRINT(XSpeed);
    PRINT(YawSpeed);
#endif

    pRobot->SetSpeed(XSpeed, YawSpeed);
}

void S_Tracking::Exit(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nSaindo do S_Tracking" << endl;
#endif
}