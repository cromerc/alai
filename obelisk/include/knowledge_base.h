#ifndef OBELISK_KNOWLEDGE_BASE_H
#define OBELISK_KNOWLEDGE_BASE_H

#include "models/action.h"
#include "models/entity.h"
#include "models/fact.h"
#include "models/rule.h"
#include "models/suggest_action.h"
#include "models/verb.h"

#include <sqlite3.h>

#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace obelisk
{
    /**
     * @brief The KnowledgeBase class represents a collection of facts, rules,
     * actions, and related language connectors.
     *
     */
    class KnowledgeBase
    {
        private:
            /**
             * @brief The filename of the opened KnowledgeBase.
             *
             */
            const char* filename_;

            /**
             * @brief The SQLite connection handle.
             *
             */
            sqlite3* dbConnection_ = nullptr;

            /**
             * @brief The user passed flags to use when opening the database.
             *
             */
            int flags_;

            /**
             * @brief Enable foreign key functionality in the open database.
             *
             * This must always be done when the connection is opened or it will
             * not enforce the foreign key constraints.
             */
            void enableForeignKeys();

            /**
             * @brief Create the tables in the database.
             *
             * @param[in] function This function is called to create the table.
             */
            void createTable(std::function<const char*()> function);

        public:
            /**
             * @brief Construct a new KnowledgeBase object.
             *
             * @param[in] filename The name of the file to save the knowledge
             * base as.
             * @param[in] flags The flags to open the KnowledgeBase with.
             */
            KnowledgeBase(const char* filename, int flags);

            /**
             * @brief Construct a new KnowledgeBase object.
             *
             * @param[in] filename The name of the file to save the knowledge
             * base as.
             */
            KnowledgeBase(const char* filename) :
                KnowledgeBase(filename,
                    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE)
            {
            }

            /**
             * @brief Destroy the KnowledgeBase object.
             *
             * This will close the opened KnowledgeBase before destroying it.
             */
            ~KnowledgeBase();

            /**
             * @brief Add entities to the KnowledgeBase.
             *
             * @param[in,out] entities The entities to add. If the insert is
             * successful it will have a row ID, if not the ID will be 0.
             */
            void addEntities(std::vector<obelisk::Entity>& entities);

            /**
             * @brief Add verbs to the KnowledgeBase.
             *
             * @param[in,out] verbs The verbs to add. If the insert is
             * successful it will have a row ID, if not the ID will be 0.
             */
            void addVerbs(std::vector<obelisk::Verb>& verbs);

            /**
             * @brief Add actions to the KnowledgeBase.
             *
             * @param[in,out] actions The actions to add. If the insert is
             * successful it will have a row ID, if nto the ID will be 0.
             */
            void addActions(std::vector<obelisk::Action>& actions);

            /**
             * @brief Add facts to the KnowledgeBase.
             *
             * @param[in,out] facts The facts to add. If the insert is
             * successful it will have a row ID, if not the ID will be 0.
             */
            void addFacts(std::vector<obelisk::Fact>& facts);

            /**
             * @brief Add suggested actions to the KnowledgeBase.
             *
             * @param[in,out] suggestActions The suggested actions to add. If
             * the insert is successful it will have a row ID, if not the ID
             * will be 0.
             */
            void addSuggestActions(
                std::vector<obelisk::SuggestAction>& suggestActions);

            /**
             * @brief Add rules to the KnowledgeBase.
             *
             * @param[in,out] rules The rules to add. If the insert is
             * successful it will have a row ID, if not the ID will be 0.
             */
            void addRules(std::vector<obelisk::Rule>& rules);

            /**
             * @brief Get an Entity object based on the ID it contains.
             *
             * @param[in,out] entity The Entity object should contain just the
             * ID and the rest will be filled in.
             */
            void getEntity(obelisk::Entity& entity);

            /**
             * @brief Get a Verb object based on the ID it contains.
             *
             * @param[in,out] verb The Verb object should contain just the ID
             * and the rest will be filled in.
             */
            void getVerb(obelisk::Verb& verb);

            /**
             * @brief Get an Action based on the ID it contains.
             *
             * @param[in] action The Action object should contain just the ID
             * and the rest will be filled in.
             */
            void getAction(obelisk::Action& action);

            /**
             * @brief Get a Fact object based on the ID it contains.
             *
             * @param[in,out] fact The Fact object should contain just the ID
             * and the rest will be filled in.
             */
            void getFact(obelisk::Fact& fact);

            /**
             * @brief Get a SuggestAction based on the ID it contains.
             *
             * @param[in,out] suggestAction The SuggestAction object should
             * contain just the ID and the rest will be filled in.
             */
            void getSuggestAction(obelisk::SuggestAction& suggestAction);

            /**
             * @brief Get a Rule based on the ID it contains.
             *
             * @param[in,out] rule The Rule object should  contain just the ID
             * and the rest will be filled in.
             */
            void getRule(obelisk::Rule& rule);

            /**
             * @brief Check if a rule looks for this Fact, if so update its
             * truth.
             *
             * @param[in,out] fact The Fact to check for existing rules.
             */
            void checkRule(obelisk::Fact& fact);

            /**
             * @brief Update the is true field in the KnowledgeBase.
             *
             * @param[in,out] fact The fact to update.
             */
            void updateIsTrue(obelisk::Fact& fact);

            /**
             * @brief Query the KnowledgeBase to see if a Fact is true or false.
             *
             * @param[in] fact The Fact to check.
             */
            void queryFact(obelisk::Fact& fact);

            /**
             * @brief Query the KnowledgeBase to get a suggested action based
             * on a Fact.
             * If a SuggestAction doesn't exist, it will return an empty Action.
             *
             * @param[in] fact The Fact to search for.
             * @param[out] action The Action that is suggested to take.
             */
            void querySuggestAction(obelisk::Fact& fact,
                obelisk::Action& action);

            /**
             * @brief Take a float and divide it into 2 floats.
             *
             * This is useful to store doubles in SQLite since SQLite doesn't
             * have a double type. Instead just store the 2 floats in the
             * database. Then after selecting them combine them.
             *
             * @param[out] result1 The first float generated from the double.
             * @param[out] result2 The second float generated from the double.
             * @param[in] var The double to split into the 2 floats.
             */
            void getFloat(float& result1, float& result2, double var);

            /**
             * @brief Combines 2 separated floats back into a double.
             *
             * This will recombine the separated floats from the getFloat
             * method.
             *
             * @param[out] result The double generated from the combined floats.
             * @param[in] var1 The first float to combine.
             * @param[in] var2 The second float to combine.
             */
            void getDouble(double& result, float var1, float var2);
    };

    /**
     * @brief Exception thrown by the KnowledgeBase.
     *
     */
    class KnowledgeBaseException : public std::exception
    {
        private:
            /**
             * @brief The error message given.
             *
             */
            const std::string errorMessage_;

        public:
            /**
             * @brief Construct a new KnowledgeBaseException object.
             *
             */
            KnowledgeBaseException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            /**
             * @brief Construct a new KnowledgeBaseException object.
             *
             * @param[in] errorMessage The error message given when thrown.
             */
            KnowledgeBaseException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            /**
             * @brief Get the error message that occurred.
             *
             * @return const char* Returns the error message.
             */
            const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }
    };
} // namespace obelisk

#endif
