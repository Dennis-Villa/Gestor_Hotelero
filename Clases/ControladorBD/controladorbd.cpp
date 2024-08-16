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

Cliente* ControladorBD::crearCliente(QString nombre, QString email, QString nacionalidad, QString telefono)
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

                QString nombreCliente = query.value("nombre").toString();
                QString emailCliente = query.value("email").toString();
                QString telefonoCliente = query.value("telefono").toString();
                QString nacionalidadCliente = query.value("nacionalidad").toString();
                int cantidadEstancias = query.value("cantidad_estancias").toInt();

                return new Cliente(identificadorCliente, nombreCliente, emailCliente,
                                   nacionalidadCliente, telefonoCliente, cantidadEstancias);
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
                    int idCliente = query.value("id").toInt();
                    QString nombreCliente = query.value("nombre").toString();
                    QString emailCliente = query.value("email").toString();
                    QString telefonoCliente = query.value("telefono").toString();
                    QString nacionalidadCliente = query.value("nacionalidad").toString();
                    int cantidadEstancias = query.value("cantidad_estancias").toInt();

                    clientes.push_back(Cliente(idCliente, nombreCliente, emailCliente,
                                               nacionalidadCliente, telefonoCliente, cantidadEstancias));
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
            int idCliente = query.value("id").toInt();
            QString nombreCliente = query.value("nombre").toString();
            QString emailCliente = query.value("email").toString();
            QString telefonoCliente = query.value("telefono").toString();
            QString nacionalidadCliente = query.value("nacionalidad").toString();
            int cantidadEstancias = query.value("cantidad_estancias").toInt();

            try{
                return new Cliente(idCliente, nombreCliente, emailCliente,
                                   nacionalidadCliente, telefonoCliente, cantidadEstancias);
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












// void Controladordb::limpiar_tabla_mercado(){
//     QSqlQuery query(this->db);
//     query.prepare("DELETE FROM RegistrarMercado");
//     if(query.exec()){
//         qDebug()<<"Exito al limpiar la tabla mercado";
//     }
//     else{
//         qDebug()<<"Falló al limpiar la tabla mercado";
//         throw runtime_error("");
//     }
// }

