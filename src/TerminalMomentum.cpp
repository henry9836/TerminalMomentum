// Internal
#include "calc-example.h"

// Standard Lib
#include <filesystem>
#include <iostream>
#include <fstream>

// FTXUI
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>       // Input, Renderer, Vertical
#include <ftxui/component/component_base.hpp>  // ComponentBase
#include <ftxui/component/component_options.hpp>  // InputOptions
#include <ftxui/screen/screen.hpp> // Screen
#include <ftxui/component/screen_interactive.hpp> // ScreenInteractive
#include <ftxui/dom/elements.hpp>  // text, hbox, separator, Element, vbox, border
#include <ftxui/util/ref.hpp>  // Ref

using namespace std;
using namespace ftxui;

// TODO: Use the file path in the conf file instead
const string FileExtension = ".tm";
const string DefaultFilePath = "notes";
const string PreferredEditor = "nano";

string UserInputBuffer = "";

void OpenFile(const string& FilePath)
{
    // TODO: Refactor this to not be unsafe
    system(("nano " + FilePath).c_str());
}

void ProcessInputAction(Event event)
{
    if (event == Event::Return)
    {    
        const string FilePath = DefaultFilePath + "/" + UserInputBuffer + FileExtension;

        // If the file does not exist then create it
        if (!filesystem::exists(FilePath))
        {
            ofstream(FilePath);
        }
        
        // Open the file
        OpenFile(FilePath);

        // Clear the buffer
        UserInputBuffer = "";
    }
}

void InitalizeEnviroment()
{
    // Create the note directory if it does not exist
    if (!std::filesystem::exists(DefaultFilePath))
    {
        filesystem::create_directory(DefaultFilePath);
    }
}

int main()
{
    // Init Software
    InitalizeEnviroment();

    // Retrieve user input
    Component InputTestComponent = Input(&UserInputBuffer, "Search");

    // // Filter out non-digit characters.
    // InputTestComponent |= CatchEvent([&](Event event) {
    //     return event.is_character() && !std::isdigit(event.character()[0]);
    // });
    
    // Hook into user input
    InputTestComponent |= CatchEvent([&](Event event) {
        ProcessInputAction(event);
        return (event == Event::Return);
    });

    // Component tree
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
    
    // Init loop
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);

    return 0;
}
