

class Rect{
    private:                //Attributes
        int x1;                 //- x1 : int        (- for private)
        int x2;
        int y1;
        int y2;
    public:                 //--------------------------------
        Rect(int ax, int ay, int bx, int by);   //Rect(ax : int, ay : int ...)
        ~Rect();        //Destructor
        int width();
        int height();
        int area();
};