#include <iostream>
#include <string>
#include <cassert>

#include <pqxx/pqxx>

int main(int argc, char *argv[])
{
  pqxx::connection c("dbname=db_test user=postgres password=a");

  c.prepare("create",
            "INSERT INTO provinces (id, name, population) \
            VALUES ($1, $2, $3)");
  c.prepare("read_by_id",
            "SELECT * FROM provinces WHERE id = $1");
  c.prepare("read_by_name",
            "SELECT * FROM provinces WHERE name = $1");
//  c.prepare("update_by_id",
    //        "UPDATE provinces SET population = population + 1 \
  //          WHERE id = $1");
//  c.prepare("delete_by_id",
  //          "DELETE FROM provinces WHERE id = $1");

  {
    pqxx::work txn(c);
    pqxx::result res;

    int test_id = 9999;
    std::string test_name = "test name";
    int test_population = 50;

    // --- Create ---
    {
      txn.prepared("create")(test_id)(test_name)(test_population)
        .exec();

      res = txn.prepared("read_by_id")(test_id).exec();

      if (res.size() == 0)
      {
        std::cerr <<
          "No records with name " << test_name << ", were found." <<
          std::endl;

        return -1;
      }

      int province_id = res[0][0].as<int>();
      assert(province_id == test_id);

      std::string province_name = res[0][1].as<std::string>();
      assert(province_name.compare(test_name) == 0);

      int province_population = res[0][2].as<int>();
      assert(province_population == test_population);

      std::cout << "Province #" << province_id <<
        ", has name: " << province_name <<
        ", and population: " << province_population << std::endl;
    }

    // --- Update ---
  //  {
     // std::cout << "Updating province with id: " << test_id <<
        //std::endl;

      //txn.prepared("update_by_id")(test_id).exec();

     // res = txn.prepared("read_by_id")(test_id).exec();

     // int province_population = res[0][2].as<int>();
    //  assert(province_population == test_population + 1);
    //}

    // --- Delete ---
   // {
     // txn.prepared("delete_by_id")(test_id).exec();

     // res = txn.prepared("read_by_id")(test_id).exec();
     // assert(res.size() == 0);
   // }

    txn.commit();
  }
}
