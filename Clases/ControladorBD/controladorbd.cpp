#include "controladorbd.h"

ControladorBD::ControladorBD()
{
    this->bd = QSqlDatabase::addDatabase("QSQLITE");
    this->bd.setDatabaseName("../../db_hotel.db");
}

ControladorBD::~ControladorBD()
{
    this->bd.close();
}

bool ControladorBD::abreBD()
{
    if(this->bd.open())
    {
        qDebug() << "La base de datos abrió correctamente";
        return true;
    }
    else
    {
        throw runtime_error("La base de datos no abrió correctamente");
        return false;
    }
}

Cliente* ControladorBD::crearCliente(QString nombre, QString email, QString telefono, QString nacionalidad)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("INSERT INTO clientes (nombre, email, telefono, nacionalidad) VALUES (:nombre, :email, :telefono, :nacionalidad)");
        query.bindValue(":nombre", nombre);
        query.bindValue(":email", email);
        query.bindValue(":telefono", telefono);
        query.bindValue(":nacionalidad", nacionalidad);

        if (query.exec())
        {
            qDebug() << "Exito al guardar el cliente en la base de datos";
            int idCliente = query.lastInsertId().toInt();

            try{
                Cliente *nuevoCliente = new Cliente(idCliente, nombre, email, nacionalidad, telefono);
                return nuevoCliente;
            }
            catch(invalid_argument &ex)
            {
                this->eliminarCliente(idCliente);

                throw;
            }
        }
        else
        {
            throw runtime_error("Fallo al guardar el cliente en la base de datos");
            qDebug() << "Fallo al guardar el cliente en la base de datos.";
        }
    }

    return nullptr;
}

Cliente* ControladorBD::buscarCliente(int identificadorCliente)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("SELECT * FROM clientes WHERE id = :id");
        query.bindValue(":id", identificadorCliente);

        if (query.exec())
        {
            qDebug() << "Exito al buscar el cliente en la base de datos";

            if (query.first())
            {
                qDebug() << "Cliente encontrado en la base de datos";

                QString nombre = query.value("nombre").toString();
                QString email = query.value("email").toString();
                QString telefono = query.value("telefono").toString();
                QString nacionalidad = query.value("nacionalidad").toString();
                int estancias = query.value("cantidad_estancias").toInt();

                return new Cliente(identificadorCliente, nombre, email,
                                   nacionalidad, estancias, telefono);
            }
            else
            {
                throw runtime_error("El cliente no existe en la base de datos");
                qDebug() << "El cliente no existe en la base de datos";
            }
        }
        else
        {
            throw runtime_error("Fallo al buscar el cliente en la base de datos");
            qDebug() << "Fallo al buscar el cliente en la base de datos.";
        }
    }

    return nullptr;
}

vector<Cliente> ControladorBD::getClientes()
{
    vector <Cliente> clientes;

    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("SELECT * FROM clientes");

        if (query.exec())
        {
            qDebug() << "Exito al obtener clientes de la base de datos";

            if (query.first())
            {
                while(query.next())
                {
                    int id = query.value("id").toInt();
                    QString nombre = query.value("nombre").toString();
                    QString email = query.value("email").toString();
                    QString telefono = query.value("telefono").toString();
                    QString nacionalidad = query.value("nacionalidad").toString();
                    int estancias = query.value("cantidad_estancias").toInt();

                    clientes.push_back(Cliente(id, nombre, email, nacionalidad,
                                               estancias, telefono));
                }
            }
            else
            {
                qDebug() << "No existen clientes en la base de datos";
            }
        }
        else
        {
            throw runtime_error("Fallo al obtener clientes de la base de datos");
            qDebug() << "Fallo al obtener clientes de la base de datos.";
        }
    }

    return clientes;
}

Cliente* ControladorBD::aniadirEstancia(int identificadorCliente)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("UPDATE clientes SET cantidad_estancias = cantidad_estancias + 1 WHERE id = :id");
        query.bindValue(":id", identificadorCliente);

        if (query.exec())
        {
            qDebug() << "Exito al modificar el cliente en la base de datos";

            int id = query.value("id").toInt();
            QString nombre = query.value("nombre").toString();
            QString email = query.value("email").toString();
            QString telefono = query.value("telefono").toString();
            QString nacionalidad = query.value("nacionalidad").toString();
            int estancias = query.value("cantidad_estancias").toInt();

            try{
                return new Cliente(id, nombre, email, nacionalidad,
                                   estancias, telefono);
            }
            catch(invalid_argument &ex)
            {
                query.prepare("UPDATE clientes SET cantidad_estancias = cantidad_estancias - 1 WHERE id = :id");
                query.bindValue(":id", identificadorCliente);

                query.exec();

                throw;
            }
        }
        else
        {
            throw runtime_error("Fallo al modificar el cliente en la base de datos");
            qDebug() << "Fallo al modificar el cliente en la base de datos.";
        }
    }

    return nullptr;
}

void ControladorBD::eliminarCliente(int identificadorCliente)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("DELETE FROM clientes WHERE id = :id");
        query.bindValue(":id", identificadorCliente);

        if (query.exec())
        {
            qDebug() << "Exito al eliminar el cliente de la base de datos";
        }
        else
        {
            throw runtime_error("Fallo al eliminar el cliente de la base de datos");
            qDebug() << "Fallo al eliminar el cliente de la base de datos.";
        }
    }
}

Habitacion *ControladorBD::crearHabitacion(int numero, QString tipo, int tamanio, int numeroCamas, float costeNoche)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("INSERT INTO habitaciones (numero_habitacion, tipo_habitacion,"
                      "tamanio_m2, numero_camas, coste_noche) VALUES "
                      "(:numero, :tipo, :tamanio, :camas, :coste)");
        query.bindValue(":numero", numero);
        query.bindValue(":tipo", tipo);
        query.bindValue(":tamanio", tamanio);
        query.bindValue(":camas", numeroCamas);
        query.bindValue(":coste", costeNoche);

        if (query.exec())
        {
            qDebug() << "Exito al guardar la habitación en la base de datos";

            try{
                Habitacion *nuevaHabitacion = new Habitacion(numero, tipo, tamanio,
                                                             numeroCamas, costeNoche);
                return nuevaHabitacion;
            }
            catch(invalid_argument &ex)
            {
                this->eliminarHabitacion(numero);

                throw;
            }
        }
        else
        {
            throw runtime_error("Fallo al guardar la habitación en la base de datos");
            qDebug() << "Fallo al guardar la habitación en la base de datos.";
        }
    }

    return nullptr;
}

Habitacion *ControladorBD::buscarHabitacion(int numero)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("SELECT * FROM habitaciones WHERE numero_habitacion = :numero");
        query.bindValue(":numero", numero);

        if (query.exec())
        {
            qDebug() << "Exito al buscar la habitación en la base de datos";

            if (query.first())
            {
                qDebug() << "Habitación encontrada en la base de datos";

                QString tipo = query.value("tipo_habitacion").toString();
                int tamanio = query.value("tamanio_m2").toInt();
                int numeroCamas = query.value("numero_camas").toInt();
                float costeNoche = query.value("coste_noche").toFloat();
                bool disponible = query.value("disponible").toBool();
                bool enArreglos = query.value("en_arreglos").toBool();

                return new Habitacion(numero, tipo, tamanio, numeroCamas,
                                      costeNoche, disponible, enArreglos);
            }
            else
            {
                throw runtime_error("La habitación no existe en la base de datos");
                qDebug() << "La habitación no existe en la base de datos";
            }
        }
        else
        {
            throw runtime_error("Fallo al buscar la habitación en la base de datos");
            qDebug() << "Fallo al buscar la habitación en la base de datos.";
        }
    }

    return nullptr;
}

vector<Habitacion> ControladorBD::getHabitaciones()
{
    vector <Habitacion> habitaciones;

    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("SELECT * FROM habitaciones");

        if (query.exec())
        {
            qDebug() << "Exito al obtener las habitaciones de la base de datos";

            if (query.first())
            {
                while(query.next())
                {
                    int numero = query.value("numero_habitacion").toInt();
                    QString tipo = query.value("tipo_habitacion").toString();
                    int tamanio = query.value("tamanio_m2").toInt();
                    int numeroCamas = query.value("numero_camas").toInt();
                    float costeNoche = query.value("coste_noche").toFloat();
                    bool disponible = query.value("disponible").toBool();
                    bool enArreglos = query.value("en_arreglos").toBool();

                    habitaciones.push_back(Habitacion(numero, tipo, tamanio, numeroCamas,
                                                      costeNoche, disponible, enArreglos));
                }
            }
            else
            {
                qDebug() << "No existen habitaciones en la base de datos";
            }
        }
        else
        {
            throw runtime_error("Fallo al obtener las habitaciones de la base de datos");
            qDebug() << "Fallo al obtener las habitaciones de la base de datos.";
        }
    }

    return habitaciones;
}

Habitacion *ControladorBD::cambiarDisponibilidadHabitacion(int numero, bool disponible)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("SELECT disponible, en_arreglos FROM habitaciones WHERE numero_habitacion = :numero");
        query.bindValue(":numero", numero);

        if (query.exec())
        {
            bool previoDisponible = query.value("disponible").toBool();
            bool enArreglos = query.value("en_arreglos").toBool();

            if (enArreglos && disponible)
            {
                throw logic_error("Una habitación en arreglos no puede hacerse disponible.");
                qDebug() << "Una habitación en arreglos no puede hacerse disponible.";
            }
            else
            {
                query.prepare("UPDATE habitaciones SET disponible = :disponible WHERE numero_habitacion = :numero");
                query.bindValue(":numero", numero);
                query.bindValue(":disponible", disponible);

                if (query.exec())
                {
                    qDebug() << "Exito al modificar la habitación en la base de datos";

                    QString tipo = query.value("tipo_habitacion").toString();
                    int tamanio = query.value("tamanio_m2").toInt();
                    int numeroCamas = query.value("numero_camas").toInt();
                    float costeNoche = query.value("coste_noche").toFloat();

                    try{
                        return new Habitacion(numero, tipo, tamanio, numeroCamas,
                                              costeNoche, disponible, enArreglos);
                    }
                    catch(invalid_argument &ex)
                    {
                        query.prepare("UPDATE habitaciones SET disponible = :disponible WHERE numero_habitacion = :numero");
                        query.bindValue(":numero", numero);
                        query.bindValue(":disponible", previoDisponible);

                        query.exec();

                        throw;
                    }
                }
                else
                {
                    throw runtime_error("Fallo al modificar la habitación en la base de datos");
                    qDebug() << "Fallo al modificar la habitación en la base de datos.";
                }
            }
        }
        else
        {
            throw runtime_error("Fallo en la consulta de arreglos.");
            qDebug() << "Fallo en la consulta de arreglos.";
        }
    }

    return nullptr;
}

Habitacion *ControladorBD::cambiarEnArreglosHabitacion(int numero, bool enArreglos)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("SELECT disponible FROM habitaciones WHERE numero_habitacion = :numero");
        query.bindValue(":numero", numero);

        if (query.exec())
        {
            bool previoDisponible = query.value("disponible").toBool();

            query.prepare("UPDATE habitaciones SET disponible = :disponible, en_arreglos = :enArreglos "
                          "WHERE numero_habitacion = :numero");
            query.bindValue(":numero", numero);
            query.bindValue(":disponible", (enArreglos ? false : previoDisponible) );
            query.bindValue(":enArreglos", enArreglos);

            if (query.exec())
            {
                qDebug() << "Exito al modificar la habitación en la base de datos";

                QString tipo = query.value("tipo_habitacion").toString();
                int tamanio = query.value("tamanio_m2").toInt();
                int numeroCamas = query.value("numero_camas").toInt();
                float costeNoche = query.value("coste_noche").toFloat();
                bool disponible = query.value("disponible").toBool();

                try{
                    return new Habitacion(numero, tipo, tamanio, numeroCamas,
                                          costeNoche, disponible, enArreglos);
                }
                catch(invalid_argument &ex)
                {
                    query.prepare("UPDATE habitaciones SET disponible = :disponible, en_arreglos = :enArreglos "
                                  "WHERE numero_habitacion = :numero");
                    query.bindValue(":numero", numero);
                    query.bindValue(":disponible", previoDisponible);
                    query.bindValue(":enArreglos", !enArreglos);

                    query.exec();

                    throw;
                }
            }
            else
            {
                throw runtime_error("Fallo al modificar la habitación en la base de datos");
                qDebug() << "Fallo al modificar la habitación en la base de datos.";
            }
        }
        else
        {
            throw runtime_error("Fallo en la consulta de disponibilidad.");
            qDebug() << "Fallo en la consulta de disponibilidad.";
        }
    }

    return nullptr;
}

void ControladorBD::eliminarHabitacion(int numero)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("DELETE FROM habitaciones WHERE numero_habitacion = :numero");
        query.bindValue(":numero", numero);

        if (query.exec())
        {
            qDebug() << "Exito al eliminar la habitación de la base de datos";
        }
        else
        {
            throw runtime_error("Fallo al eliminar la habitación de la base de datos");
            qDebug() << "Fallo al eliminar la habitación de la base de datos.";
        }
    }
}
