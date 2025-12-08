//Date.h

class Date{
    private: 
        int day;
        int month;
        int year;
    public:
        Date();
        Date(int d, int m, int year);

        void setDate(int d, int m, int y);
        int getDay();
        int getMonth();
        int getYear();
};