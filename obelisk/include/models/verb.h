#ifndef OBELISK_MODELS_VERB_H
#define OBELISK_MODELS_VERB_H

#include <sqlite3.h>

#include <string>

namespace obelisk
{
    /**
     * @brief The Verb model represents a verb which is used to connnect
     * entities.
     *
     */
    class Verb
    {
        private:
            /**
             * @brief The ID of the Verb in the KnowledgeBase.
             *
             */
            int id_;

            /**
             * @brief The name of the Verb.
             *
             */
            std::string name_;

        public:
            /**
             * @brief Construct a new Verb object.
             *
             */
            Verb() :
                id_(0),
                name_("")
            {
            }

            /**
             * @brief Construct a new Verb object.
             *
             * @param[in] id The ID of the Verb.
             */
            Verb(int id) :
                id_(id),
                name_("")
            {
            }

            /**
             * @brief Construct a new Verb object.
             *
             * @param[in] name The name of the Verb.
             */
            Verb(std::string name) :
                id_(0),
                name_(name)
            {
            }

            /**
             * @brief Construct a new Verb object.
             *
             * @param[in] id The ID of the Verb.
             * @param[in] name The name of the Verb.
             */
            Verb(int id, std::string name) :
                id_(id),
                name_(name)
            {
            }

            /**
             * @brief Create the Verb table in the KnowledgeBase.
             *
             * @return const char* Returns the query used to create the table.
             */
            static const char* createTable();

            /**
             * @brief Get the ID of the Verb.
             *
             * @return int& Returns the ID.
             */
            int& getId();

            /**
             * @brief Set the ID of the Verb.
             *
             * @param[in] id Set the ID of the Verb.
             */
            void setId(int id);

            /**
             * @brief Get the name of the Verb.
             *
             * @return std::string& The Verb name.
             */
            std::string& getName();

            /**
             * @brief Set the name of the Verb.
             *
             * @param[in] name The Verb name.
             */
            void setName(std::string name);

            /**
             * @brief Select a verb by name from the KnowledgeBase.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void selectByName(sqlite3* dbConnection);

            /**
             * @brief Insert a new verb into the KnowledgeBase.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void insert(sqlite3* dbConnection);
    };
} // namespace obelisk

#endif
