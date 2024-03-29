#ifndef PARAMETERS_H
#define	PARAMETERS_H

/* se definido, mostra informações na tela durante a execução do programa */
#define DEBUG

/* habilitar somente 1 dos dois: ou HOKUYO, ou SICK */
#define HOKUYO  //se estiver usando o HOKUYO
//#define SICK  //se estiver usando o SICK

/* habilitar somente 1 dos dois: ou ROBO_SIMULADO, ou ROBO_REAL */
//#define ROBO_SIMULADO        //se estiver usando o ambiente simulado
#define ROBO_REAL          //se estiver usando o ambiente real

#ifdef SICK
#define LASERNAME               "SICK"
#define FOV                     180
#define SAMPLES                 181
#define NOMINALRANGE            8.0                                             //8 metros de alcance
#endif

#ifdef HOKUYO
#define LASERNAME               "HOKUYO"
#define FOV                     (682*360/1024.0)                                //239.765625 (tirado do datasheet do Hokuyo)
#define SAMPLES                 683
#define NOMINALRANGE            4.0                                             //4.0 metros de alcance
#endif

#define XSPEED_LIMIT            0.2                                             //velocidade máxima recomendada
#define YAWSPEED_LIMIT          1.5                                             //velocidade máxima de giro recomendada
#define MAXRANGE                (NOMINALRANGE-BOXSIZE)                          //maior comprimento detectável pelo laser
#define MINRANGE                BOXSIZE                                         //menor comprimento detectável pelo laser
#define DETECTIONBOX_LENGTH     1.5                                             //comprimento de detecção
#define DETECTIONBOX_WIDTH      1.5                                             //largura de detecão
#define DETECTION_DISTANCE      1.3                                             //a partir de que distância começa a perseguir (usado na transição S_InitialSetup -> S_Tracking)
#define BOXSIZE                 0.08                                            //precisão da visão do robô. É o tamanho da aresta da caixa de visão
#define COLLISION_THRESHOLD     0.4                                             //distância, em metros, que o robô considera como uma possível colisão com obstáculos

/* Estamos sendo "gastadores". Dá pra diminuir a matriz
 * de visão um pouco mais. Assumimos que o robô enxerga
 * pra trás também, como se FOV fosse 360 graus */
#define BOXES_ROWS              ceil(2*NOMINALRANGE/BOXSIZE)                    //#linhas de caixas
#define BOXES_COLUMNS           ceil(2*NOMINALRANGE/BOXSIZE)                    //#colunas de caixas

#define ANGULAR_RESOLUTION      ((double)(FOV/(SAMPLES-1)))
#define LASER_0DEG              ((int)((FOV-180)/(2.0*ANGULAR_RESOLUTION)))
#define LASER_90DEG             ((int)(SAMPLES-1)/2)
#define LASER_180DEG            ((int)(SAMPLES-1-LASER_0DEG))
#define LASER_FIRST             0
#define LASER_LAST              (SAMPLES-1)
#define DEGREE(feixe)           (feixe*ANGULAR_RESOLUTION-(FOV-180)/2.0)
#define RADIAN(feixe)           DTOR(DEGREE(feixe))
#define LASER_W_DEG(d)          ((int)(LASER_0DEG + d/ANGULAR_RESOLUTION))      //laser number with degree d
#define PRINT(x)                std::cout << #x << ": " << x << std::endl;
#define COUT(x)                 std::cout << x << std::endl;

#define LASER_INFO                                                             \
    do { std::cout                                                             \
             << "\nLASER in use: " << LASERNAME                                \
             << "\nFOV: " << FOV                                               \
             << "\nSAMPLES: " << SAMPLES                                       \
             << "\nNOMINALRANGE: " << NOMINALRANGE                             \
             << "\nLASER_0DEG: " << LASER_0DEG                                 \
             << "\nLASER_90DEG: " << LASER_90DEG                               \
             << "\nLASER_180DEG: " << LASER_180DEG                             \
             << "\nANGULAR_RESOLUTION: " << ANGULAR_RESOLUTION                 \
             << "\nDEGREE(0): " << DEGREE(0)                                   \
             << "\nRADIAN(0): " << RADIAN(0)                                   \
             << "\nDETECTIONBOX_LENGTH: " << DETECTIONBOX_LENGTH               \
             << "\nDETECTIONBOX_WIDTH: " << DETECTIONBOX_WIDTH                 \
             << "\nBOXSIZE: " << BOXSIZE                                       \
             << "\nDETECTION_DISTANCE: " << DETECTION_DISTANCE                 \
             << "\nCOLLISION_THRESHOLD: " << COLLISION_THRESHOLD               \
             << "\nXSPEED_LIMIT: " << XSPEED_LIMIT                             \
             << "\nYAWSPEED_LIMIT: " << YAWSPEED_LIMIT                         \
             << "\nMAXRANGE: " << MAXRANGE                                     \
             << "\nMINRANGE: " << MINRANGE                                     \
             << "\nBOXES_ROWS: " << BOXES_ROWS                                 \
             << "\nBOXES_COLUMNS: " << BOXES_COLUMNS                           \
             << "\n\n" << std::endl;                                           \
    } while(0)

enum Referencial {
    REFERENCIAL_MATRIX, //referencial na posição (1,1) da matriz de visão
    REFERENCIAL_ROBOT //referencial no centro da matriz de visão
};

#endif	/* PARAMETERS_H */