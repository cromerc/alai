#ifndef OBELISK_MODELS_SUGGEST_ACTION_H
#define OBELISK_MODELS_SUGGEST_ACTION_H

#include "models/action.h"
#include "models/fact.h"

#include <string>

namespace obelisk
{
    /**
     * @brief The SuggestAction model representas the actions to take depending
     * on if the Fact is true or false.
     *
     */
    class SuggestAction
    {
        private:
            /**
             * @brief The ID of the SuggestAction.
             *
             */
            int id_;

            /**
             * @brief The Fact to check the truth of.
             *
             */
            obelisk::Fact fact_;

            /**
             * @brief The Action to take if the Fact is true.
             *
             */
            obelisk::Action trueAction_;

            /**
             * @brief The Action to take if the Fact is false.
             *
             */
            obelisk::Action falseAction_;

        public:
            /**
             * @brief Construct a new SuggestAction object.
             *
             */
            SuggestAction() :
                id_(0),
                fact_(),
                trueAction_(),
                falseAction_()
            {
            }

            /**
             * @brief Construct a new SuggestAction object.
             *
             * @param[in] id The ID of the SuggestAction in the KnowledgeBase.
             */
            SuggestAction(int id) :
                id_(id),
                fact_(),
                trueAction_(),
                falseAction_()
            {
            }

            /**
             * @brief Construct a new SuggestAction object.
             *
             * @param[in] fact The Fact.
             * @param[in] trueAction The true Action.
             * @param[in] falseAction The false Action.
             */
            SuggestAction(obelisk::Fact fact,
                obelisk::Action trueAction,
                obelisk::Action falseAction) :
                id_(0),
                fact_(fact),
                trueAction_(trueAction),
                falseAction_(falseAction)
            {
            }

            /**
             * @brief Construct a new SuggestAction object.
             *
             * @param[in] id The ID of the SuggestAction in the KnowledgeBase.
             * @param[in] fact The Fact.
             * @param[in] trueAction The true Action.
             * @param[in] falseAction The false Action.
             */
            SuggestAction(int id,
                obelisk::Fact fact,
                obelisk::Action trueAction,
                obelisk::Action falseAction) :
                id_(id),
                fact_(fact),
                trueAction_(trueAction),
                falseAction_(falseAction)
            {
            }

            /**
             * @brief Create the SuggestAction table in the database.
             *
             * @return const char* Returns the query used to create the table.
             */
            static const char* createTable();

            /**
             * @brief Get the ID of the SuggestAction.
             *
             * @return int& Returns the ID.
             */
            int& getId();

            /**
             * @brief Set the ID of the SuggestAction.
             *
             * @param[in] id The new ID.
             */
            void setId(int id);

            /**
             * @brief Get the Fact object.
             *
             * @return obelisk::Fact& Returns the Fact.
             */
            obelisk::Fact& getFact();

            /**
             * @brief Set the Fact object.
             *
             * @param[in] fact The new Fact.
             */
            void setFact(obelisk::Fact fact);

            /**
             * @brief Get the true Action object.
             *
             * @return obelisk::Action& Returns the true Action.
             */
            obelisk::Action& getTrueAction();

            /**
             * @brief Set the true Action object.
             *
             * @param[in] trueAction The new true Action.
             */
            void setTrueAction(obelisk::Action trueAction);

            /**
             * @brief Get the false Action object.
             *
             * @return obelisk::Action& Returns the false Action.
             */
            obelisk::Action& getFalseAction();

            /**
             * @brief Set the false Action object.
             *
             * @param[in] falseAction The new false Action.
             */
            void setFalseAction(obelisk::Action falseAction);

            /**
             * @brief Select the SuggestAction from the KnowledgeBase by IDs of
             * the sub-objects.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void selectById(sqlite3* dbConnection);

            /**
             * @brief Insert the SuggestAction into the KnowledgeBase.
             *
             * @param[in] dbConnection The database connection to use.
             */
            void insert(sqlite3* dbConnection);
    };
} // namespace obelisk

#endif
