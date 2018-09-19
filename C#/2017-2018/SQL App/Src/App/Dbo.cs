using Npgsql;
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App
{
    class Dbo
    {
        private static string ipAddress = "";
        private static string userName = "";
        private static string password = "";
        private static string dataBase = "";

        public static NpgsqlConnection connection;

        public static void ConnectToDatabase()
        {
            GetCredentials();
            String connectionString = String.Format("Server={0};User Id={1};Password={2};Database={3}",
                ipAddress, userName, password, dataBase);
            connection = new NpgsqlConnection(connectionString);
            connection.Open();
        }

        private static void GetCredentials()
        {
            StreamReader reader = new StreamReader(@"settings.txt");
            string line = reader.ReadLine();
            ipAddress = line.Split('=')[1];
            line = reader.ReadLine();
            userName = line.Split('=')[1];
            line = reader.ReadLine();
            password = line.Split('=')[1];
            line = reader.ReadLine();
            dataBase = line.Split('=')[1];
        }

        public static DataTable GetWholeTable(string tableName)
        {
            return GetTable(SqlQueryConsts.SELECT_ALL_QUERY + "\"" + tableName + "\"");
        }

        public static void CloseConnection()
        {
            connection.Close();
        }

        public static DataTable GetTable(string query)
        {
            NpgsqlCommand command = new NpgsqlCommand(query, connection);
            return GetTable(command);
        }

        public static DataTable GetTable(NpgsqlCommand command)
        {
            DataTable table = new DataTable();
            NpgsqlDataAdapter dataAdapter = new NpgsqlDataAdapter(command);
            dataAdapter.Fill(table);
            return table;
        }

        public static DataTable GetTablesFromSchema()
        {
            return GetTable(SqlQueryConsts.ALL_TABLES_QUERY);
        }
        
        public static int Execute(string query)
        {
            NpgsqlCommand command = new NpgsqlCommand(query, connection);
            return command.ExecuteNonQuery();
        }


        public static DataTable GetTable(string tableName, List<Conditional> conditionals, params string[] columns)
        {
            string allColumnsToOne = columns.Length == 0 ? "*" : String.Join(",", columns);
            string allConditonalsToOne = conditionals.Count == 0 ? "TRUE" : String.Join(" AND ", conditionals);

            string query = String.Format("Select {0} FROM \"{1}\" WHERE {2}", allColumnsToOne, tableName, allConditonalsToOne);
            return GetTable(query);
        }

        public static void InsertValues(string tableName, params string[] values)
        {
            string allValuesToOne = String.Join(",", values);
            string query = String.Format("INSERT INTO {0} VALUES ({1})", tableName, allValuesToOne);
            Execute(query);
        }
        
        public static void DeleteValues(string tableName, List<Conditional> conditionals)
        {
            string allConditonalsToOne = String.Join(" AND ", conditionals);
            string query = String.Format("DELETE FROM {0} WHERE {1}", tableName, allConditonalsToOne);
            Execute(query);
        }
    }
}
