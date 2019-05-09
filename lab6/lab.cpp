#include <cstdlib>
#include <iostream>
#include <fstream>
#include <config.h>
#include <curl/curl.h>
#include <FL/Fl_Cairo_Window.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>
 
/*
Compilation command:
g++ -g -I/home/debian -o "lab" "lab.cpp" -lcurl getImageURL.cpp -I/home/debian/fltk-1.3.4-2 `fltk-config --cxxflags --ldflags --use-images --use-cairo`
g++ -g -I/home/debian -o "lab" "lab.cpp" -lcurl getImage.cpp -I/home/debian/fltk-1.3.4-2 `fltk-config --cxxflags --ldflags --use-images --use-cairo`
 */
 
//Fl_Cairo_Window cw;
const int WIDTH = 300;
const int HEIGHT = 300;
 
std::string getImageURL(std::string);
void getImage(std::string);
std::string parseJson(std::string s);
 
int main()
{
     std::string s = getImageURL("cat"); //return the location URL of a cat image
     s = parseJson(s);
   
    //~ std::cout << s << std::endl;
   
    Fl_Cairo_Window cw(WIDTH, HEIGHT);
   
    Fl_Box b(10, 10, WIDTH, HEIGHT);
   
    /* go get the file returned by getImageURL store in a file */  
    getImage("https://media3.giphy.com/media/wPud2z0g029Xy/200.gif");
   
    Fl_GIF_Image i("animal.gif");
   
    b.image(&i);
   
    cw.show();
   
    //~ while (true)
    //~ {
        //~ switch( fl_choice("Empty Trash?", "Yes", "No", 0) )
        //~ {
            //~ case 0:
                //~ {std::cout << "Yes" << std::endl; break;}   //yes
            //~ case 1:
                //~ {std::cout << "No" << std::endl; break;}    //No (default)
        //~ }
    //~ }
   
    //std::cout << fl_input("Enter new animal: ");
   
    return Fl::run();
   
}
