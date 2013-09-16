#ifndef UPDAO_H
#define UPDAO_H

#include <vector>
#include"userpassword.h"
#include"sqlite3.h"

namespace pmsm {
    class UPDao
    {
        public:
            UPDao();
            ~UPDao();

            void createUserPassword(UserPassword up);
            void removeUserPasswordById(long id);
            void removeUserPassword(UserPassword up);
            void modifyUserPassword(UserPassword up);
            std::vector<UserPassword*> *getAllUserPassword();
            UserPassword* getUserPasswordById(long id);
        private:
            sqlite3* db;
    };
}

#endif // UPDAO_H
