#include <iostream>
#include <sqlite3.h> 
#include "mobservice.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   Mob *mob = (Mob *)data;
   mob->name = argv[1];
   mob->isHostile = std::stoi(argv[2]) == 1 ? true : false;
   mob->isBoss = std::stoi(argv[3]) == 1 ? true : false;
   mob->baseHealth = std::stoi(argv[4]);
   mob->scaledHealth = std::stoi(argv[5]);
   mob->baseDamage = std::stoi(argv[6]);
   mob->scaledDamage = std::stoi(argv[7]);
   mob->baseSpeed = std::stoi(argv[8]);
   mob->scaledSpeed = std::stoi(argv[9]);
   return 0;
}

Mob getMob(int id) {
   Mob mob;
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   std::string sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("../database/Mob.db", &db);

   /* Create SQL statement */
   sql = "SELECT * from Mob WHERE Id = "+std::to_string(id);

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, &mob, &zErrMsg);

   sqlite3_close(db);
   return mob;
} 