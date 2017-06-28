#ifndef MYSQL_INTERFACE_H__
#define MYSQL_INTERFACE_H__

#include <string>
#include <vector>

#include <windows.h>

#include "mysql.h"
#include "winsock.h"

#include "wx/string.h"

class MySQLInterface {
public:
  MySQLInterface();
  virtual ~MySQLInterface();

  bool ConnectMysql(const wxString& server,
                    const wxString& username,
                    const wxString& password,
                    const wxString& database,
                    int port);

  bool CreateDatabase(std::string& dbname);
  bool CreateDBTable(const std::string& query);

  void ErrorInfo();
  bool WriteDataToDB(std::string query_str);
  bool GetDataFromDB(std::string query_str, std::vector<std::vector<std::string>>& data);
  void CloseMysql();

public:
  int error_num_;                    //error no
  wxString error_info_;             //error info

private:
  MYSQL mysql_instance_;                      //MySQL instance
  MYSQL_RES* result_;
};

#endif  // MYSQL_INTERFACE_H_
