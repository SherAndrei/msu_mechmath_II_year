#include <fstream>
#include "tags.h"
#include "doc.h"

int main() {
    std::ofstream file("file.svg");
    Document doc;
    Rect canvas({1, 1}, 1920, 1080);
    doc.AddTag(&canvas);

    Rect flag({960, 340}, 300, 150);
    doc.AddTag(&flag);

    Rect blue({960, 390}, 300, 50, Color("blue"));
    doc.AddTag(&blue);

    Rect red({960, 440}, 300, 50, Color("red"));
    doc.AddTag(&red);

    Circle head({860, 540}, 80, Color(224, 177, 132));
    doc.AddTag(&head);

    Line body({860, 620}, {860, 880}, Color("black"), Color("black"), 15);
    doc.AddTag(&body);

    Polyline legs({{760, 1080}, {860, 880}, {960, 1080}}, Color("none"), Color("black"), 15);
    doc.AddTag(&legs);

    Polyline arms({{760, 840}, {860, 640}, {960, 840}}, Color("none"), Color("black"), 15);
    doc.AddTag(&arms);

    Line stick({960, 340}, {960, 1080});
    doc.AddTag(&stick);

    Text text({660, 240}, "Росия вперде!", {0, 0}, 128);
    doc.AddTag(&text);

    doc.Print(file);
}
