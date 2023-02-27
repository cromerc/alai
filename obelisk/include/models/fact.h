#ifndef OBELISK_MODELS_FACT_H
#define OBELISK_MODELS_FACT_H

#include "models/action.h"
#include "models/entity.h"
#include "models/fact.h"
#include "models/verb.h"

#include <string>

namespace obelisk
{
    /**
     * @brief The Fact model represents truth in the releationship between two
     * entities separated by a verb.
     *
     */
    class Fact
    {
        private:
            /**
             * @brief The ID of the Fact in the KnowledgeBase.
             *
             */
            int id_;

            /**
             * @brief The Entity from the left side of the expression.
             *
             */
            obelisk::Entity leftEntity_;

            /**
             * @brief The Entity from the right side of the expression.
             *
             */
            obelisk::Entity rightEntity_;

            /**
             * @brief The Verb that represents the relationship in the
             * expression.
             *
             */
            obelisk::Verb verb_;

            /**
             * @brief Whether or not the fact is considered true or not.
             *
             */
            double isTrue_;

        public:
            /**
             * @brief Construct a new Fact object.
             *
             */
            Fact() :
                id_(0),
                leftEntity_(),
                rightEntity_(),
                verb_(),
                isTrue_(0)
            {
            }

            /**
             * @brief Construct a new Fact object.
             *
             * @param[in] id The ID of the Fact in the KnowledgeBase.
             */
            Fact(int id) :
                id_(id),
                leftEntity_(),
                rightEntity_(),
                verb_(),
                isTrue_(0)
            {
            }

            /**
             * @brief Construct a new Fact object.
             *
             * @param[in] leftEntity The Entity on the left side of the
             * expression.
             * @param[in] rightEntity The Entity on the right side of the
             * expression.
             * @param[in] verb The Verb separating the entities.
             * @param[in] isTrue Whether or not the fact is true.
             */
            Fact(obelisk::Entity leftEntity,
                obelisk::Entity rightEntity,
                obelisk::Verb verb,
                double isTrue = 0) :
                id_(0),
                leftEntity_(leftEntity),
                rightEntity_(rightEntity),
                verb_(verb),
                isTrue_(isTrue)
            {
            }

            /**
             * @brief Construct a new Fact object.
             *
             * @param[in] id The ID of the Fact in the KnowledgeBase.
             * @param[in] leftEntity The Entity on the left side of the
             * expression.
             * @param[in] rightEntity The Entity on the right side of the
             * expression.
             * @param[in] verb The Verb separating the entities.
             * @param[in] isTrue Whether or not the fact is true.
             */
            Fact(int id,
                obelisk::Entity leftEntity,
                obelisk::Entity rightEntity,
                obelisk::Verb verb,
                double isTrue = 0) :
                id_(id),
                leftEntity_(leftEntity),
                rightEntity_(rightEntity),
                verb_(verb),
                isTrue_(isTrue)
            {
            }

            /**
             * @brief Create the Fact table in the KnowledgeBase.
             *
             * @return const char* Returns the query used to create the table.
             */
            static const char* createTable();

            /**
             * @brief Get the ID of the Fact
             *
             * @return int& Returns the ID.
             */
            int& getId();

            /**
             * @brief Set the ID of the Fact.
             *
             * @param[in] id Set the ID of the Fact.
             */
            void setId(int id);

            /**
             * @brief Get the left Entity object.
             *
             * @return Entity& The left Entity.
             */
            Entity& getLeftEntity();

            /**
             * @brief Set the left Entity object.
             *
             * @param[in] leftEntity The left Entity to set.
             */
            void setLeftEntity(obelisk::Entity leftEntity);

            /**
             * @brief Get the right Entity object.
             *
             * @return Entity& The right Entity.
             */
            Entity& getRightEntity();

            /**
             * @brief Set the right Entity object.
             *
             * @param[in] rightEntity The right Entity to set.
             */
            void setRightEntity(obelisk::Entity rightEntity);

            /**
             * @brief Get the Verb object.
             *
             * @return Verb& The Verb.
             */
            Verb& getVerb();

            /**
             * @brief Set the Verb object.
             *
             * @param[in] verb The Verb.
             */
            void setVerb(obelisk::Verb verb);

            /**
             * @brief Gets the isTrue value.
             *
             * @return true If the Fact is considered true.
             * @return false If the Fact is considered false.
             */
            double& getIsTrue();

            /**
             * @brief Set the Fact as true or false.
             *
             * @param[in] isTrue Whether or not the Fact is true.
             */
            void setIsTrue(double isTrue);

            /**
             * @brief Select the Fact from the KnowledgeBase by IDs of the
             * sub-objects.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void selectById(sqlite3* dbConnection);

            /**
             * @brief Select the Fact from the KnowledgeBase by the name's of
             * the entities and verb.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void selectByName(sqlite3* dbConnection);

            /**
             * @brief Select an Action from the KnowledgeBase using the provided
             * Fact.
             *
             * @param[in] dbConnection The database connection to use.
             * @param[out] action The Action to take based on the provided fact.
             */
            void selectActionByFact(sqlite3* dbConnection,
                obelisk::Action& action);

            /**
             * @brief Insert the Fact into the KnowledgeBase.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void insert(sqlite3* dbConnection);

            /**
             * @brief Update whether or not the fact is true in the
             * KnowledgeBase.
             *
             * @param[in] dbConnection The database connection.
             */
            void updateIsTrue(sqlite3* dbConnection);
    };
} // namespace obelisk

#endif
