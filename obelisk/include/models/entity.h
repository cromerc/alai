#ifndef OBELISK_MODELS_ENTITY_H
#define OBELISK_MODELS_ENTITY_H

#include <sqlite3.h>

#include <string>

namespace obelisk
{
    /**
     * @brief The Entity model represents either a left or right side entity,
     * typically used in facts and rules.
     *
     */
    class Entity
    {
        private:
            /**
             * @brief The ID of the Entity in the KnowledgeBase.
             *
             */
            int id_;

            /**
             * @brief The name of the Entity.
             *
             */
            std::string name_;

        public:
            /**
             * @brief Construct a new Entity object.
             *
             */
            Entity() :
                id_(0),
                name_("")
            {
            }

            /**
             * @brief Construct a new Entity object.
             *
             * @param[in] id The ID of the Entity.
             */
            Entity(int id) :
                id_(id),
                name_("")
            {
            }

            /**
             * @brief Construct a new Entity object.
             *
             * @param[in] name The name of the Entity.
             */
            Entity(std::string name) :
                id_(0),
                name_(name)
            {
            }

            /**
             * @brief Construct a new Entity object.
             *
             * @param[in] id The ID of the Entity.
             * @param[in] name The name of the Entity.
             */
            Entity(int id, std::string name) :
                id_(id),
                name_(name)
            {
            }

            /**
             * @brief Create the table in the KnowledgeBase.
             *
             * @return const char* Returns the query used to create the table.
             */
            static const char* createTable();

            /**
             * @brief Get the ID of the Entity.
             *
             * @return int& Returns the ID.
             */
            int& getId();

            /**
             * @brief Set the ID of the Entity.
             *
             * @param[in] id The ID of the Entity.
             */
            void setId(int id);

            /**
             * @brief Get the name of the Entity.
             *
             * @return std::string& The name of the Entity.
             */
            std::string& getName();

            /**
             * @brief Set the name of the Entity.
             *
             * @param[in] name The name of the Entity.
             */
            void setName(std::string name);

            /**
             * @brief Select an Entity from the KnowledgeBase based on the
             * object's name.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void selectByName(sqlite3* dbConnection);

            /**
             * @brief Insert an Entity into the KnowledgeBase based on the
             * object's fields.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void insert(sqlite3* dbConnection);
    };
} // namespace obelisk

#endif
