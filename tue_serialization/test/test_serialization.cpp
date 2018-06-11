#include <tue/serialization/archive.h>
#include <tue/serialization/input_archive.h>
#include <tue/serialization/output_archive.h>

#include <tue/serialization/filesystem.h>
#include <tue/serialization/version.h>

#include <fstream>

int main(int argc, char **argv) {

    std::string test_filename = "/tmp/tue_test_serialization";

    {
        // example
        double d = 3.15;
        float f = 5.0;
        int i = 123;
        std::string s = "Hello, this is just a simple test";

        tue::serialization::Archive a_out;
        a_out << d << f << i << s;

        tue::serialization::toFile(a_out, test_filename);
    }

    {
        tue::serialization::Archive a_in;
        tue::serialization::fromFile(test_filename, a_in);

        // read
        double d;
        float f;
        int i;
        std::string s;

        a_in >> d >> f >> i >> s;

        std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
        std::cout << a_in.version() << std::endl;
    }

    tue::serialization::Archive a;

    {
        // example
        double d = 3.15;
        float f = 5.0;
        int i = 123;
        std::string s = "Hello, this is just a simple test";

        a << d << f << i << s;
    }

    {
        // read
        double d;
        float f;
        int i;
        std::string s;

        a >> d >> f >> i >> s;

        std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
    }

    return 0;
}
