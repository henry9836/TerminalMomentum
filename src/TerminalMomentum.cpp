#include <iostream>
#include <fstream>
#include <ftxui/screen/screen.hpp>
#include "calc-example.h"

 
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

using namespace std;
using namespace ftxui;

int main()
{
    string InputTest;

    Component InputTestComponent = Input(&InputTest, "Search");

    // // Filter out non-digit characters.
    // InputTestComponent |= CatchEvent([&](Event event) {
    //     return event.is_character() && !std::isdigit(event.character()[0]);
    // });
    
    // Filter out returns
    InputTestComponent |= CatchEvent([&](Event event) {
        if (event == Event::Return)
        {
            ofstream outfile(InputTest);
            outfile.close();
            // Invoke a std::system call but have the editor used be whitelisted
            // The name of the text file will also have to be santised
            InputTest = "";
        }
        return (event == Event::Return);
    });

    // The component tree:
    auto component = Container::Vertical({
        InputTestComponent,
    });
    
    // Tweak how the component tree is rendered:
    auto renderer = Renderer(component, [&] {
        return vbox({
                hbox(InputTestComponent->Render()) | border,
                text("Results") | border | flex,
                text("Preview")  | border,
        });
    });
    
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);

    return 0;
}


