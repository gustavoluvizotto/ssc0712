//#ifndef VECTOR_H
//#define VECTOR_H
//
//template <typename g_Type2>
//class Vector {
//private:
//    Point<g_Type2> p1, p2, p3;
//    Point<g_Type2> vector1, vector2;
//public:
//
//    Vector(g_Type2 point1, g_Type2 point2, g_Type2 point3) {
//        this->p1 = point1;
//        this->p2 = point2;
//        this->p3 = point3;
//        this->vector1 = point2 - point1;
//        this->vector2 = point3 - point1;
//    }
//
//    double getAngleBetweenVectors() { // between the 2 vectors atributes
//        double theta;
//        g_Type2 v1Scalar, v2Scalar;
//        v1Scalar = this->getNorma(this->vector1);
//        v2Scalar = this->getNorma(this->vector2);
//        theta = acos((double)(dotProduct()/(v1Scalar*v2Scalar)));
//        return theta;
//    }
//
//    g_Type2 dotProduct() {
//        return (this->vector1.getX() * this->vector2.getX() +
//                this->vector1.getY() * this->vector2.getY());
//    }
//
//    g_Type2 getNorma(g_Type2 vector) {  // it'll be a Point vector...
//        return sqrt(pow(vector.getX(), 2) + pow(vector.getY(), 2));
//    }
//};
//
//#endif  /* VECTOR_H */
