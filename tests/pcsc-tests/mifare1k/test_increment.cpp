#include "logicalaccess/dynlibrary/idynlibrary.hpp"
#include "logicalaccess/dynlibrary/librarymanager.hpp"
#include "logicalaccess/readerproviders/readerconfiguration.hpp"
#include "logicalaccess/services/storage/storagecardservice.hpp"
#include "pluginscards/mifare/mifarechip.hpp"

#include "lla-tests/macros.hpp"
#include "lla-tests/utils.hpp"

void introduction()
{
    prologue();
    PRINT_TIME("This test target Mifare1K cards. It tests the implementation of "
               "the increment and decrement commands");

    PRINT_TIME("You will have 20 seconds to insert a card. Test log below");
    PRINT_TIME("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    LLA_SUBTEST_REGISTER("WriteValueBlock");
    LLA_SUBTEST_REGISTER("ReadValueBlock");
    LLA_SUBTEST_REGISTER("Increment");
    LLA_SUBTEST_REGISTER("Decrement");
}

void read_value_block(std::shared_ptr<logicalaccess::MifareCommands> cmd)
{
    auto key = std::make_shared<logicalaccess::MifareKey>("ff ff ff ff ff ff");
    cmd->loadKey(0, logicalaccess::MifareKeyType::KT_KEY_A, key->getData(), key->getLength());
    cmd->authenticate(32, 0, logicalaccess::MifareKeyType::KT_KEY_A);

    std::vector<uint8_t> tmp;
    using namespace logicalaccess;
    tmp = cmd->readBinary(32, 16);
    PRINT_TIME("Raw read data: " << tmp);

    unsigned int value;
    uint8_t backup;
    cmd->readValueBlock(32, value, backup);
    LLA_ASSERT(value == 42424242, "Invalid value");
    LLA_ASSERT(backup == 33, "Invalid backup block number");
    LLA_SUBTEST_PASSED("ReadValueBlock");
}

void write_value_block(std::shared_ptr<logicalaccess::MifareCommands> cmd)
{
    auto key = std::make_shared<logicalaccess::MifareKey>("ff ff ff ff ff ff");
    cmd->loadKey(0, logicalaccess::MifareKeyType::KT_KEY_A, key->getData(), key->getLength());
    cmd->authenticate(32, 0, logicalaccess::MifareKeyType::KT_KEY_A);

    cmd->writeValueBlock(32, 42424242, 33);
    LLA_SUBTEST_PASSED("WriteValueBlock");
}

void increment(std::shared_ptr<logicalaccess::MifareCommands> cmd)
{
    auto key = std::make_shared<logicalaccess::MifareKey>("ff ff ff ff ff ff");
    cmd->loadKey(0, logicalaccess::MifareKeyType::KT_KEY_A, key->getData(), key->getLength());
    cmd->authenticate(32, 0, logicalaccess::MifareKeyType::KT_KEY_A);

    cmd->increment(32, 10);
    unsigned int value;
    uint8_t backup;
    cmd->readValueBlock(32, value, backup);
    LLA_ASSERT(value == 42424252, "Invalid value");
    LLA_SUBTEST_PASSED("Increment");
}

void decrement(std::shared_ptr<logicalaccess::MifareCommands> cmd)
{
    auto key = std::make_shared<logicalaccess::MifareKey>("ff ff ff ff ff ff");
    cmd->loadKey(0, logicalaccess::MifareKeyType::KT_KEY_A, key->getData(), key->getLength());
    cmd->authenticate(32, 0, logicalaccess::MifareKeyType::KT_KEY_A);

    cmd->decrement(32, 20);
    unsigned int value;
    uint8_t backup;
    cmd->readValueBlock(32, value, backup);
    LLA_ASSERT(value == 42424232, "Invalid value");
    LLA_SUBTEST_PASSED("Decrement");
}

int main(int, char **)
{
    introduction();
    ReaderProviderPtr provider;
    ReaderUnitPtr readerUnit;
    ChipPtr chip;
    std::tie(provider, readerUnit, chip) = pcsc_test_init();

    PRINT_TIME("CHip identifier: " <<
               logicalaccess::BufferHelper::getHex(chip->getChipIdentifier()));

    LLA_ASSERT(chip->getCardType() == "Mifare1K",
               "Chip is not a Mifare1K, but is " + chip->getCardType() +
               " instead.");


    auto cmd = std::dynamic_pointer_cast<logicalaccess::MifareCommands>(chip->getCommands());
    auto profile = std::dynamic_pointer_cast<logicalaccess::MifareProfile>(chip->getProfile());

    // Get the root node
    std::shared_ptr<logicalaccess::LocationNode> rootNode = chip->getRootLocationNode();
    // Get childrens of this node
    std::vector<std::shared_ptr<logicalaccess::LocationNode> > childs = rootNode->getChildrens();

    write_value_block(cmd);
    read_value_block(cmd);
    increment(cmd);
    decrement(cmd);

    pcsc_test_shutdown(readerUnit);
    return 0;
}
