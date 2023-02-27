#ifndef OBELISK_INCLUDE_OBELISK_H
#define OBELISK_INCLUDE_OBELISK_H

#include "knowledge_base.h"

#include <memory>
#include <string>

/**
 * @brief The obelisk namespace contains everything needed to compile obelisk
 * code.
 *
 */
namespace obelisk
{
    /**
     * @brief The obelisk library provides everything needed to consult the
     * KnowledgeBase.
     *
     */
    class Obelisk
    {
        private:
            std::unique_ptr<obelisk::KnowledgeBase> kb_;

        public:
            /**
             * @brief Construct a new Obelisk object.
             *
             */
            Obelisk(std::string filename);

            /**
             * @brief Destroy the Obelisk object.
             *
             */
            ~Obelisk() = default;

            /**
             * @brief Get the obelisk version.
             *
             * @return std::string The version.
             */
            std::string getVersion();

            /**
             * @brief Get the obelisk library so version.
             *
             * @return int The version.
             */
            int getLibVersion();

            /**
             * @brief Query the obelisk KnowledgeBase to see if a Fact is true
             * or not.
             *
             * @param[in] p_obelisk The obelisk object pointer.
             * @param[in] left_entity The left entity.
             * @param[in] verb The verb.
             * @param[in] right_entity The right entity.
             * @return double Returns whether or not the Fact is true.
             */
            double query(const std::string& leftEntity,
                const std::string& verb,
                const std::string& rightEntity);

            /**
             * @brief Query the Obelisk KnowledgeBase and return the suggested
             * action to take.
             *
             * @param[in] leftEntity The left entity.
             * @param[in] verb The verb.
             * @param[in] rightEntity The right entity.
             * @return std::string Returns the suggested action.
             */
            std::string queryAction(const std::string& leftEntity,
                const std::string& verb,
                const std::string& rightEntity);
    };
} // namespace obelisk

#endif
