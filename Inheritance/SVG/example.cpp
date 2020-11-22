#include <fstream>
#include "doc.h"
#include "tags.h"


int main() {
    std::ofstream file("ex.svg");
    Document doc;
    Polyline pl({{100, 100}, {500, 500}, {400, 50}},
                Color("green"), Color(200, 100, 15), 3);
    Circle c({200, 200}, 30, Color("red"), Color("none"), 1);
    Text t({25, 60}, "The text should be placed here",
           {-5, 10}, 22, "Verdana", Color("black"), Color("yellow"), 1);
    doc.AddTag(&pl);
    doc.AddTag(&c);
    doc.AddTag(&t);
    doc.Print(file);
}
