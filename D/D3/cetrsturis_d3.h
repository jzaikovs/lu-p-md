
//klase
class Square
{
//noklusējumā privātie mainīgie
    double a,b,c,d;
    int angle;
public:

    //metožu prototips

    Square(double _a, double _b, double _c, double _d,int _angle); //konstruktors
    ~Square(); //dekonstruktors
    void Mainit(double _a, double _b, double _c, double _d,int _angle);
    void Aprekins();
    void Drukat();
};
