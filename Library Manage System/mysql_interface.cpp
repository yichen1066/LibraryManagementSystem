#include "mysql_interface.h"

MySQLInterface::MySQLInterface()
    : error_num_(0)
    , error_info_("ok") {
  mysql_library_init(0, NULL, NULL);
  mysql_init(&mysql_instance_);
  mysql_options(&mysql_instance_, MYSQL_SET_CHARSET_NAME, "gbk");
}

MySQLInterface::~MySQLInterface() {
}

//Connect to MySQL
bool MySQLInterface::ConnectMysql(const wxString& server,
                                  const wxString& username,
                                  const wxString& password,
                                  const wxString& database,
                                  int port) {
  if (mysql_real_connect(&mysql_instance_, server, username, password, database, port, 0, 0) != NULL)
    return true;
  else
    ErrorInfo();
  return false;
}

bool MySQLInterface::CreateDatabase(std::string& dbname) {
  std::string queryStr = "create database if not exists ";
  queryStr += dbname;

  if (0 == mysql_query(&mysql_instance_, queryStr.c_str())) {
    queryStr = "use ";
    queryStr += dbname;
    if (0 == mysql_query(&mysql_instance_, queryStr.c_str())) {
      return true;
    }
  }

  ErrorInfo();
  return false;
}

bool MySQLInterface::CreateDBTable(const std::string& query) {
  if (0 == mysql_query(&mysql_instance_, query.c_str())) {
    return true;
  }
  ErrorInfo();
  return false;
}

void MySQLInterface::ErrorInfo() {
  error_info_ = "Can't Connect to Database";
}

bool MySQLInterface::WriteDataToDB(std::string query_str) {
  if (0 == mysql_query(&mysql_instance_, query_str.c_str()))
    return true;
  else
    ErrorInfo();
  return false;
}

bool MySQLInterface::GetDataFromDB(std::string query_str, std::vector<std::vector<std::string>>& data) {
  if (0 != mysql_query(&mysql_instance_, query_str.c_str())) {
    ErrorInfo();
    return false;
  }

  result_ = mysql_store_result(&mysql_instance_);

  int row = mysql_num_rows(result_);
  int field = mysql_num_fields(result_);

  MYSQL_ROW line = NULL;
  line = mysql_fetch_row(result_);

  int j = 0;
  std::string temp;

  while (NULL != line) {
    std::vector<std::string> linedata;

    for (int i = 0; i < field; i++) {
      if (line[i]) {
        temp = line[i];
        linedata.push_back(temp);
      } else {
        temp = "";
        linedata.push_back(temp);
      }
    }

    line = mysql_fetch_row(result_);
    data.push_back(linedata);
  }
  return true;
}
