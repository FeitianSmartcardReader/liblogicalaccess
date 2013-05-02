/**
 * \file CardService.cpp
 * \author Maxime CHAMLEY <maxime.chamley@islog.eu>
 * \brief Card service.
 */

#include "logicalaccess/Services/CardService.h"
#include "logicalaccess/Cards/CardProvider.h"


namespace LOGICALACCESS
{
	CardService::CardService(boost::shared_ptr<CardProvider> cardProvider)
	{
		d_cardProvider = cardProvider;
	}

	boost::shared_ptr<CardProvider> CardService::getCardProvider()
	{
		return d_cardProvider;
	}
}
