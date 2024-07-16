#include <iostream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "calc-example.h"

using namespace std;
using namespace ftxui;

int main()
{
    printf("hi\n");

    cout << "Testing 1 + 3: " << Calc::add(1, 3) << endl;

    // Define the document
    Element document =
        hbox({
        text("left")   | border,
        text("this is a ftxui test :3") | border | flex,
        text("right")  | border,
        });
    
    auto screen = Screen::Create(
        Dimension::Full(),       // Width
        Dimension::Fit(document) // Height
    );
    Render(screen, document);
    screen.Print();

    return 0;
}


