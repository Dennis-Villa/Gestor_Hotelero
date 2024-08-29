#ifndef EXCEPTION_RESERVA_VENCIDA_H
#define EXCEPTION_RESERVA_VENCIDA_H

#endif // EXCEPTION_RESERVA_VENCIDA_H

#include <exception>
#include <string>

using namespace std;

class exception_reserva_vencida : public std::exception {

public:
    exception_reserva_vencida(const char * mensaje){
        this->mensaje = mensaje;
    }

    const char* what() const throw()
    {
        return this->mensaje.c_str();
    }

private:
    string mensaje;
};
