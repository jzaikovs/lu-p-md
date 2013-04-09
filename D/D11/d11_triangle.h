
//klase
class Triangle
{
    //noklusējumā privātie mainīgie trijstūra malu garumi
    double a,b,c;

public:

    //metožu prototips
    Triangle(double a, double b, double c); //konstruktors
    ~Triangle(); //dekonstruktors
    void Triangle::Mainit(double change_a, double change_b, double change_c);
    void Aprekins();
    void Drukat();
};
