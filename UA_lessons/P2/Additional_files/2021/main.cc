// 48150407 MARTÍNEZ GARCÍA, ÁLVARO
#include  <iostream>
using namespace std;

#include "Calendar.h"

int main() {
    Calendar c;
    c.addEvent("", "4-6-2021 10:00", 240);
    c.addEvent("Examen física", "4-6-2021 10:00", 240);
    c.addEvent("Examen matemáticas", "4-6-2021 14:00", 120);
    cout << c;
    c.addEvent("Examen P2", "4-6-2021 9:00", 180);
    cout << c;
}
