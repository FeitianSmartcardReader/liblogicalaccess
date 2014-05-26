/**
 * \file SAMCommands.hpp
 * \author Adrien J. <adrien.jund@islog.com>
 * \brief SAMAV2Commands commands.
 */

#ifndef LOGICALACCESS_SAMAV2COMMANDS_HPP
#define LOGICALACCESS_SAMAV2COMMANDS_HPP

namespace logicalaccess
{
	class LIBLOGICALACCESS_API SAMAV2Commands
	{
		public:		
			virtual std::vector<unsigned char> dumpSecretKey(unsigned char keyno, unsigned char keyversion, std::vector<unsigned char> divInpu) = 0;
	};
}

#endif /* LOGICALACCESS_SAMAV2COMMANDS_HPP */

