#ifndef PARAMETERS_H
#define	PARAMETERS_H

#define DEBUG
#define HOKUYO  //se estiver usando o HOKUYO
//#define SICK  //se estiver usando o SICK

#ifdef SICK
#define LASERNAME               "SICK"
#define FOV                     180
#define SAMPLES                 181
#define NOMINALRANGE            8                                               //8 metros de alcance
#endif

#ifdef HOKUYO
#define LASERNAME               "HOKUYO"
#define FOV                     682*360/1024.0                                  //239.765625 (tirado do datasheet do Hokuyo)
#define SAMPLES                 683
#define NOMINALRANGE            4.0                                             //4.0 metros de alcance
#endif

#define MAXRANGE                NOMINALRANGE-BOXSIZE                            //maior comprimento detectável pelo laser
#define MINRANGE                BOXSIZE                                         //menor comprimento detectável pelo laser
#define DETECTIONBOX_LENGTH     1.0                                             //comprimento de detecção
#define DETECTIONBOX_WIDTH      1.5                                             //largura de detecão
#define BOXSIZE                 0.05                                            //precisão da visão do robô. É o tamanho da aresta da caixa de visão

/* Estamos sendo "gastadores". Dá pra diminuir a matriz
 * de visão um pouco mais. Assumimos que o robô enxerga
 * pra trás também, como se FOV fosse 360 graus */
#define BOXES_LINES             ceil(2*NOMINALRANGE/BOXSIZE)                    //#linhas de caixas
#define BOXES_COLUMNS           ceil(2*NOMINALRANGE/BOXSIZE)                    //#colunas de caixas

#define ANGULAR_RESOLUTION      (double)(FOV/(SAMPLES-1))
#define LASER_0DEG              (int)((FOV-180)/(2.0*ANGULAR_RESOLUTION))
#define LASER_90DEG             (int)(SAMPLES-1)/2
#define LASER_180DEG            (int)(SAMPLES-1-LASER_0DEG)
#define LASER_FIRST             0
#define LASER_LAST              SAMPLES-1
#define ANGLEDEGREE(feixe)      feixe*ANGULAR_RESOLUTION-(FOV-180)/2.0
#define ANGLERADIAN(feixe)      DTOR(ANGLEDEGREE(feixe))
#define LASER_W_DEG(d)          (int)(LASER_0DEG + d/ANGULAR_RESOLUTION) //laser number with degree d
#define PRINT(x)                std::cout << #x << ": " << x << std::endl;


#define LASER_INFO \
    do { std::cout                                                             \
             << "\nLASER in use: " << LASERNAME                                \
             << "\nFOV: " << FOV                                               \
             << "\nSAMPLES: " << SAMPLES                                       \
             << "\nNOMINALRANGE: " << NOMINALRANGE                             \
             << "\nLASER_0DEG: " << LASER_0DEG                                 \
             << "\nLASER_90DEG: " << LASER_90DEG                               \
             << "\nLASER_180DEG: " << LASER_180DEG                             \
             << "\nANGULAR_RESOLUTION: " << ANGULAR_RESOLUTION                 \
             << "\nANGLEDEGREE(0): " << ANGLEDEGREE(0)                         \
             << "\nANGLERADIAN(0): " << ANGLERADIAN(0)                         \
             << "\nDETECTIONBOX_LENGTH: " << DETECTIONBOX_LENGTH               \
             << "\nDETECTIONBOX_WIDTH: " << DETECTIONBOX_WIDTH                 \
             << "\nMAXRANGE: " << MAXRANGE                                     \
             << "\nMINRANGE: " << MINRANGE                                     \
             << "\nBOXSIZE: " << BOXSIZE                                       \
             << "\nBOXES_LINES: " << BOXES_LINES                               \
             << "\nBOXES_COLUMNS: " << BOXES_COLUMNS                           \
             << "\n\n" << std::endl;                                           \
    } while(0)

#endif	/* PARAMETERS_H */