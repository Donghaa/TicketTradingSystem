//Class: UserCollection
//Description: 판매자 및 구매자들의 정보를 저장 및 관리하는 클래스이다.
//Author: 김동하
#include <algorithm>
#include "UserCollection.h"


UserCollection::UserCollection()
{
}

UserCollection* UserCollection::var = nullptr;

UserCollection& UserCollection::get()
{
	if (!var)
		var = new UserCollection();
	return *var;
}

void UserCollection::insert(const Buyer & buyer)
{
	buyers.push_back(buyer);
}

void UserCollection::insert(const Seller & seller)
{
	sellers.push_back(seller);
}

void UserCollection::erase(const Info & info)
{
	if (info.getUserType() == "seller") {
		auto it = std::find_if(sellers.begin(), sellers.end(), [&info](const Seller& i) { return i == info; });
		sellers.erase(it);
	}
	else {
		auto it = std::find_if(buyers.begin(), buyers.end(), [&info](const Buyer& i) { return i == info; });
		buyers.erase(it);
	}
}

std::vector<Seller>& UserCollection::getSellers()
{
	return sellers;
}

std::vector<Buyer>& UserCollection::getBuyers()
{
	return buyers;
}

std::vector<Ticket*> UserCollection::getReservableTickets(const std::string& home)
{
	std::vector<Ticket*> reservableTickets;
	//모든 판매자로부터
	for (Seller& seller : sellers) {
		//판매중인 티켓 선택
		std::vector<std::shared_ptr<Ticket>>& tickets = seller.getRegisteredTickets();

		for (auto it = tickets.begin(); it != tickets.end(); ++it)
		{
			reservableTickets.push_back(it->get());
		}
	}
	//시간순 정렬
	sort(reservableTickets.begin(), reservableTickets.end(), [](Ticket* lhs, Ticket* rhs) { return lhs->getTime() < rhs->getTime(); });

	return reservableTickets;
}

const Info * UserCollection::find(std::string id, std::string pw)
{
	auto buyerIter = std::find_if(buyers.begin(), buyers.end(), 
		[&id, &pw](const Buyer& i) { return i.getInfo().checkID(id, pw); });
	if (buyerIter != buyers.end())
		return &buyerIter->getInfo();

	auto sellerIter = std::find_if(sellers.begin(), sellers.end(), 
		[&id, &pw](const Seller& i) { return i.getInfo().checkID(id, pw); });
	if (sellerIter != sellers.end())
		return &sellerIter->getInfo();

	return nullptr;

}


std::variant<Seller*, Buyer*> UserCollection::operator[](const Info & info)
{
	if (info.getUserType() == "seller") {
		return &*find_if(sellers.begin(), sellers.end(), [&info](const Seller& i) {return i == info; });
	}
	else {
		return &*find_if(buyers.begin(), buyers.end(), [&info](const Buyer& i) {return i == info; });
	}
}
size_t UserCollection::size() const
{
	return sellers.size() + buyers.size();
}

UserCollection::~UserCollection()
{
}
