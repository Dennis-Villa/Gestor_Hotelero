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
                do
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
                while(query.next());
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
                do
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
                while(query.next());
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



Reserva *ControladorBD::crearReserva(QString estado, QDate inicio, QDate fin, int noches, int cliente, float importe, int habitacion)
{
    if (this->abreBD())
    {
        Cliente *clienteReserva = this->buscarCliente(cliente);
        Habitacion *habitacionReserva = nullptr;

        QSqlQuery query(this->bd);

        if (habitacion != -1)
        {
            habitacionReserva = this->buscarHabitacion(habitacion);

            query.prepare("INSERT INTO reservas (estado_reserva,fecha_inicio,fecha_fin,"
                          "cantidad_noches,cliente_id,importe,numero_habitacion) "
                          "VALUES (:estado,:inicio,:fin,:noches,:cliente,:importe,:habitacion)");
            query.bindValue(":estado", estado);
            query.bindValue(":inicio", inicio.toString());
            query.bindValue(":fin", fin.toString());
            query.bindValue(":noches", noches);
            query.bindValue(":cliente", cliente);
            query.bindValue(":importe", importe);
            query.bindValue(":habitacion", habitacion);
        }
        else
        {
            query.prepare("INSERT INTO reservas (estado_reserva,fecha_inicio,fecha_fin,"
                          "cantidad_noches,cliente_id,importe)"
                          "VALUES (:estado,:inicio,:fin,:noches,:cliente,:importe)");
            query.bindValue(":estado", estado);
            query.bindValue(":inicio", inicio.toString());
            query.bindValue(":fin", fin.toString());
            query.bindValue(":noches", noches);
            query.bindValue(":cliente", cliente);
            query.bindValue(":importe", importe);
        }

        if (query.exec())
        {
            qDebug() << "Exito al guardar la reserva en la base de datos";

            int numeroConfirmacion = query.lastInsertId().toInt();

            try{
                if (habitacionReserva == nullptr)
                {
                    new Reserva(numeroConfirmacion, clienteReserva, inicio, fin, noches, importe, estado);
                }
                else
                {
                    new Reserva(numeroConfirmacion, clienteReserva, inicio, fin, noches, importe, estado, habitacionReserva);
                }

                this->cambiarEstadoReserva(numeroConfirmacion, estado);
                return this->aniadirGasto(numeroConfirmacion, "Reserva Habitación", importe);
            }
            catch(invalid_argument &ex)
            {
                this->eliminarReserva(numeroConfirmacion);

                throw;
            }
            catch(logic_error &ex)
            {
                this->eliminarReserva(numeroConfirmacion);

                throw;
            }
        }
        else
        {
            throw runtime_error("Fallo al guardar la reserva en la base de datos");
            qDebug() << "Fallo al guardar la reserva en la base de datos.";
        }
    }

    return nullptr;
}

Reserva *ControladorBD::buscarReserva(int numeroConfirmacion)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("SELECT * FROM reservas WHERE numero_confirmacion = :numeroConfirmacion");
        query.bindValue(":numeroConfirmacion", numeroConfirmacion);

        if (query.exec())
        {
            qDebug() << "Exito al buscar la reserva en la base de datos";

            if (query.first())
            {
                qDebug() << "Reserva encontrada en la base de datos";

                QString estado = query.value("estado_reserva").toString();
                int noches = query.value("cantidad_noches").toInt();
                QString inicioString = query.value("fecha_inicio").toString();
                QString finString = query.value("fecha_fin").toString();
                int cliente = query.value("cliente_id").toInt();
                QVariant habitacion = query.value("numero_habitacion");
                QString gastos = query.value("desglose_gastos").toString();
                int importe = query.value("importe").toFloat();

                Cliente *clienteReserva = this->buscarCliente(cliente);
                Habitacion *habitacionReserva = nullptr;

                if (!habitacion.isNull())
                    habitacionReserva = this->buscarHabitacion(habitacion.toInt());

                return new Reserva(numeroConfirmacion, clienteReserva, noches, inicioString,
                                   finString, gastos, importe, estado, habitacionReserva);
            }
            else
            {
                throw runtime_error("La reserva no existe en la base de datos");
                qDebug() << "La reserva no existe en la base de datos";
            }
        }
        else
        {
            throw runtime_error("Fallo al buscar la reserva en la base de datos");
            qDebug() << "Fallo al buscar la reserva en la base de datos.";
        }
    }

    return nullptr;
}

vector <Reserva> ControladorBD::getReservas()
{
    vector <Reserva> reservas;

    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("SELECT * FROM reservas");

        if (query.exec())
        {
            qDebug() << "Exito al obtener las reservas de la base de datos";

            if (query.last())
            {
                do
                {
                    int numero = query.value("numero_confirmacion").toInt();
                    QString estado = query.value("estado_reserva").toString();
                    int noches = query.value("cantidad_noches").toInt();
                    QString inicioString = query.value("fecha_inicio").toString();
                    QString finString = query.value("fecha_fin").toString();
                    int clienteID = query.value("cliente_id").toInt();
                    QVariant numeroHabitacion = query.value("numero_habitacion");
                    QString gastos = query.value("desglose_gastos").toString();
                    float importe = query.value("importe").toFloat();

                    Cliente *cliente = this->buscarCliente(clienteID);
                    Habitacion *habitacion = nullptr;

                    if (!numeroHabitacion.isNull())
                        habitacion = this->buscarHabitacion(numeroHabitacion.toInt());

                    QDate inicio = QDate::fromString(inicioString);
                    QDate fin = QDate::fromString(finString);

                    reservas.push_back(Reserva(numero, cliente, noches, inicio, fin,
                                               gastos, importe, estado, habitacion));
                }
                while(query.previous());
            }
            else
            {
                qDebug() << "No existen reservas en la base de datos";
            }
        }
        else
        {
            throw runtime_error("Fallo al obtener las reservas de la base de datos");
            qDebug() << "Fallo al obtener las reservas de la base de datos.";
        }
    }

    return reservas;
}

Reserva *ControladorBD::cambiarEstadoReserva(int numeroConfirmacion, QString estado)
{
    if (this->abreBD())
    {
        Reserva *reservaACambiar = this->buscarReserva(numeroConfirmacion);

        reservaACambiar->setEstadoReserva(estado);

        if (estado == "Estancia Finalizada")
            this->aniadirEstancia(reservaACambiar->getClienteID());

        QString inicio = reservaACambiar->getFechaInicio().toString();
        QString fin = reservaACambiar->getFechaFin().toString();

        QSqlQuery query(this->bd);
        query.prepare("UPDATE reservas SET estado_reserva = :estado, fecha_inicio = :inicio, fecha_fin = :fin WHERE numero_confirmacion = :numeroConfirmacion");
        query.bindValue(":numeroConfirmacion", numeroConfirmacion);
        query.bindValue(":estado", estado);
        query.bindValue(":inicio", inicio);
        query.bindValue(":fin", fin);

        if (query.exec())
        {
            qDebug() << "Exito al modificar el estado de la reserva.";

            return reservaACambiar;
        }
        else
        {
            QSqlError error = query.lastError();
            QString errorText = "Fallo al modificar el estado de la reserva: " + error.text();
            qDebug() << errorText;
            throw runtime_error("Fallo al modificar el estado de la reserva");
        }
    }

    return nullptr;
}

Reserva *ControladorBD::aniadirGasto(int numeroConfirmacion, QString gasto, float importe)
{
    if (this->abreBD())
    {
        Reserva *reservaACambiar = this->buscarReserva(numeroConfirmacion);
        reservaACambiar->AniadirGasto(gasto, importe);

        QString gastos = reservaACambiar->convertirGastosAString();

        QSqlQuery query(this->bd);
        query.prepare("UPDATE reservas SET desglose_gastos = :gastos WHERE numero_confirmacion = :numeroConfirmacion");
        query.bindValue(":numeroConfirmacion", numeroConfirmacion);
        query.bindValue(":gastos", gastos);

        if (query.exec())
        {
            qDebug() << "Exito al modificar los gastos de la reserva.";

            return reservaACambiar;
        }
        else
        {
            QSqlError error = query.lastError();
            QString errorText = "Fallo al modificar los gastos de la reserva: " + error.text();
            qDebug() << errorText;
            throw runtime_error("Fallo al modificar los gastos de la reserva");
        }
    }

    return nullptr;
}

void ControladorBD::eliminarReserva(int numeroConfirmacion)
{
    if (this->abreBD())
    {
        QSqlQuery query(this->bd);

        query.prepare("DELETE FROM reservas WHERE numero_confirmacion = :numeroConfirmacion");
        query.bindValue(":numeroConfirmacion", numeroConfirmacion);

        if (query.exec())
        {
            qDebug() << "Exito al eliminar la reserva de la base de datos";
        }
        else
        {
            throw runtime_error("Fallo al eliminar la reserva de la base de datos");
            qDebug() << "Fallo al eliminar la reserva de la base de datos.";
        }
    }
}
