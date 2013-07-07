#ifndef TOOLBOX_H
#define	TOOLBOX_H

#include "Robot.h"
#include "Matrix.h"
#include "Point.h"
#include "Parameters.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm> //necessário para o "find" de list funcionar

using std::cout;
using std::endl;
using std::list;

namespace ToolBox {
    extern void FillVisionMatrix(Robot* pRobot, bool deteccao=false);
    extern bool isNextToFives(Matrix& matrix, int row, int col);
    extern int GetNumberOfFives(Matrix& matrix);
    extern double GetProfDistance(Matrix& matrix);
    extern Point<int> GetCMOfFives(Matrix& matrix, Referencial ref);
}

#endif	/* TOOLBOX_H */