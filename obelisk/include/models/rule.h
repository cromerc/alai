#ifndef OBELISK_MODELS_RULE_H
#define OBELISK_MODELS_RULE_H

#include "models/fact.h"

#include <string>
#include <vector>

namespace obelisk
{
    /**
     * @brief The Rule model represents a truth relation between 2 Facts.
     *
     */
    class Rule
    {
        private:
            /**
             * @brief The ID of the Rule in the KnowledgeBase.
             *
             */
            int id_;

            /**
             * @brief The Fact that depends on the Fact reason being true.
             *
             */
            obelisk::Fact fact_;

            /**
             * @brief The Fact that makes the other Fact true or false.
             *
             */
            obelisk::Fact reason_;

        public:
            /**
             * @brief Construct a new Rule object.
             *
             */
            Rule() :
                id_(0),
                fact_(),
                reason_()
            {
            }

            /**
             * @brief Construct a new Rule object.
             *
             * @param[in] id The ID of the Rule in the KnowledgeBase.
             */
            Rule(int id) :
                id_(id),
                fact_(),
                reason_()
            {
            }

            /**
             * @brief Construct a new Rule object.
             *
             * @param[in] fact The Fact.
             * @param[in] reason The reason Fact.
             */
            Rule(obelisk::Fact fact, obelisk::Fact reason) :
                id_(0),
                fact_(fact),
                reason_(reason)
            {
            }

            /**
             * @brief Construct a new Rule object.
             *
             * @param[in] id The ID of the Rule.
             * @param[in] fact The Fact.
             * @param[in] reason The reason Fact.
             */
            Rule(int id, obelisk::Fact fact, obelisk::Fact reason) :
                id_(id),
                fact_(fact),
                reason_(reason)
            {
            }

            /**
             * @brief Create the Rule table in the KnowledgeBase.
             *
             * @return const char* Returns the query used to create the table.
             */
            static const char* createTable();

            /**
             * @brief Get the ID of the Rule.
             *
             * @return int& The ID.
             */
            int& getId();

            /**
             * @brief Set the ID of the Rule.
             *
             * @param[in] id The ID.
             */
            void setId(int id);

            /**
             * @brief Get the Fact object.
             *
             * @return obelisk::Fact& The Fact.
             */
            obelisk::Fact& getFact();

            /**
             * @brief Set the Fact object.
             *
             * @param[in] fact The Fact.
             */
            void setFact(obelisk::Fact fact);

            /**
             * @brief Get the reason Fact object.
             *
             * @return obelisk::Fact& The reason Fact.
             */
            obelisk::Fact& getReason();

            /**
             * @brief Set the reason Fact object.
             *
             * @param[in] reason The reason Fact.
             */
            void setReason(obelisk::Fact reason);

            /**
             * @brief Select the Rule from the KnowledgeBase by IDs of the
             * sub-objects.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void selectById(sqlite3* dbConnection);

            /**
             * @brief Get the rules that match the reason.
             *
             * @param[in] dbConnection The database connection to use.
             * @param[out] rules The rules to fill in from the database.
             */
            static void selectByReason(sqlite3* dbConnection,
                int reasonId,
                std::vector<obelisk::Rule>& rules);

            /**
             * @brief Insert the Rule into the KnowledgeBase.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void insert(sqlite3* dbConnection);
    };
} // namespace obelisk

#endif
