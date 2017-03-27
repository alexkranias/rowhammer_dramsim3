#ifndef __COMMON_H
#define __COMMON_H

#include <iostream>

class Address {
    public:
        Address() :
            channel_(-1), rank_(-1), bankgroup_(-1), bank_(-1), row_(-1), column_(-1) {}
        Address(int channel, int rank, int bankgroup, int bank, int row, int column) :
            channel_(channel), rank_(rank), bankgroup_(bankgroup), bank_(bank), row_(row), column_(column) {}
        Address(const Address& addr) :
            channel_(addr.channel_), rank_(addr.rank_), bankgroup_(addr.bankgroup_), bank_(addr.bank_), row_(addr.row_), column_(addr.column_) {}
        int channel_;
        int rank_;
        int bankgroup_;
        int bank_;
        int row_;
        int column_;
};

enum class State {
    OPEN,
    CLOSED,
    SELF_REFRESH,
    SIZE
};

enum class CommandType {
    READ,
    READ_PRECHARGE,
    WRITE,
    WRITE_PRECHARGE,
    ACTIVATE,
    PRECHARGE,
    REFRESH_BANK,
    REFRESH,
    SELF_REFRESH_ENTER,
    SELF_REFRESH_EXIT,
    SIZE
};

class Command { 
    public:
        Command() :
            cmd_type_(CommandType::SIZE) {}
        Command(CommandType cmd_type, const Address& addr) :
            cmd_type_(cmd_type), addr_(addr) {}

        bool IsValid() { return cmd_type_ != CommandType::SIZE; }
        bool IsRefresh() { return cmd_type_ == CommandType::REFRESH || cmd_type_ == CommandType::REFRESH_BANK; }
        bool IsReadWrite() const { return cmd_type_ == CommandType::READ || cmd_type_ == CommandType::READ_PRECHARGE ||
                                          cmd_type_ == CommandType::WRITE || cmd_type_ == CommandType::WRITE_PRECHARGE; }
        CommandType cmd_type_;
        Address addr_;

        int Channel() const { return addr_.channel_ ; }
        int Rank() const { return  addr_.rank_; }
        int Bankgroup() const { return addr_.bankgroup_; }
        int Bank() const { return addr_.bank_;  }
        int Row() const { return  addr_.row_; }
        int Column() const { return addr_.column_; }

        friend std::ostream& operator<<(std::ostream& os, const Command& cmd);
};


class Request {
    public:
        Request(CommandType cmd_type, const Address& addr) :
                cmd_(Command(cmd_type, addr)), arrival_time_(-1), exit_time_(-1), id_(-1) {}
        Request(CommandType cmd_type, const Address& addr, int arrival_time, int id) :
            cmd_(Command(cmd_type, addr)), arrival_time_(arrival_time), exit_time_(-1), id_(id) {}

        Command cmd_;
        long arrival_time_;
        long exit_time_;
        int id_ = 0;

        int Channel() const { return cmd_.Channel(); }
        int Rank() const { return cmd_.Rank(); }
        int Bankgroup() const { return cmd_.Bankgroup(); }
        int Bank() const { return cmd_.Bank(); }
        int Row() const { return cmd_.Row(); }
        int Column() const { return cmd_.Column(); }

        friend std::ostream& operator<<(std::ostream& os, const Request& req);
};

#endif