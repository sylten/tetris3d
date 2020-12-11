#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <fstream>
#include <string>

using namespace std;

namespace se
{
    class Error
    {
        private:
            ofstream f;

        public:
            Error()
            {
                f.open("error.txt");
                f.close();
            }
            void operator<<(const string& s)
            {
                f.open("error.txt", ios_base::app);
                f << s << endl;
                f.close();
            }
    }err;
}

#endif // ERROR_H_INCLUDED
