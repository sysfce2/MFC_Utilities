module;

#include "pch.h"
#include <optional>
#include <sqlite_orm/sqlite_orm.h>



export module orm_util;

using namespace std::literals;

import util;

export
{

	enum class Operation { doUpdate = 1, doInsert = 2 };


	template<typename Table, typename Storage_t>
	std::optional<Table> getCurrent(CEdit& editCtrl, Storage_t& storage)
	{
		using namespace sqlite_orm;

		CString rId;
		editCtrl.GetWindowTextW(rId);
		if (rId.IsEmpty())
		{
			return std::nullopt;
		}
		auto id_str = util::from_cstring(rId);
		auto id = std::stoi(id_str);
		auto record = storage.get_optional < Table>(id);
		///////////	
		return record;
	}

	template<typename Table, typename Storage_t>
	Operation whatOperation(CEdit& editCtrl, Storage_t& storage)
	{
		auto record = getCurrent<Table>(editCtrl, storage);
		return record ? Operation::doUpdate : Operation::doInsert;
	}

	template<typename Table>
	void setIdFromRecord(CEdit& editCtrl, int pk)
	{
		editCtrl.SetWindowTextW(util::to_cstring(pk));
	}

	template<typename Data>
	void SetText(CEdit& edit_box, Data data)
	{
		edit_box.SetWindowTextW(util::to_cstring(data));
	}


	template<typename Data>
	void operator<<(CEdit& edit_box, Data data)
	{
		SetText(edit_box, data);
	}


	inline void NullText(CEdit& edit_box)
	{
		edit_box.SetWindowTextW(L"");
	}

	inline void SetColones(CEdit& edit_box, double amount)
	{
		util::Colones col{ amount };
		auto col_str = util::to_string(col);
		auto str = util::to_cstring(col_str);
		edit_box.SetWindowTextW(str);
	}

	inline void SetDolares(CEdit& edit_box, double amount)
	{
		// SetAmount(edit_box, amount);

		util::Dolares col{ amount };
		CString str = util::to_cstring(col);
		// CString str = util::dollars_to_cstring(col);
		edit_box.SetWindowTextW(str);
	}
	inline util::Dolares GetDolares(CEdit& edit_box)
	{
		CString str;
		edit_box.GetWindowTextW(str);

		util::Dolares dollars{ util::Str::from_dollars_cstring(str) };
		return dollars;
	}



	template<typename T> requires std::is_arithmetic<T>::value
		inline void SetAmount(CEdit& edit_box, T amount)
	{
		auto str = util::to_cstring(amount);
		edit_box.SetWindowTextW(str);
	}

#if 0
	inline void SetAmount(CEdit& edit_box, double amount)
	{
		auto str = util::to_cstring(amount);
		edit_box.SetWindowTextW(str);
	}

	inline void SetAmount(CEdit& edit_box, long long amount)
	{
		auto str = util::to_cstring(amount);
		edit_box.SetWindowTextW(str);
	}

	inline void SetLongLong(CEdit& edit_box, long long amount)
	{
		auto str = util::to_cstring(amount);
		edit_box.SetWindowTextW(str);
	}
#endif


	template<typename Table, int Table::* key>
	struct IdManager
	{
		CEdit& editCtrl;
		std::optional<Table>& record;
		IdManager(CEdit& editCtrl, std::optional<Table>& record)
			: editCtrl(editCtrl), record{ record }
		{}
		void SetId()
		{
			editCtrl.SetWindowTextW(util::to_cstring(record->*key));
		}
		std::optional<Table> GetIdToCurrent()
		{
			record = getCurrent<Table>(editCtrl);
		}
	};


	inline void SetDate(CDateTimeCtrl& ctrl, std::chrono::sys_days sysdate)
	{
		auto date = util::to_ole_date_time(sysdate);
		ctrl.SetTime(date);
	}

	inline std::chrono::sys_days GetDate(CDateTimeCtrl& ctrl)
	{
		COleDateTime rOleDateTime;
		ctrl.GetTime(rOleDateTime);
		std::chrono::sys_days date = util::to_sys_days(rOleDateTime);
		return date;
	}

	inline void operator>>(CDateTimeCtrl& ctrl, std::chrono::sys_days& date)
	{
		date = GetDate(ctrl);
	}

	inline void operator<<(CDateTimeCtrl& ctrl, std::chrono::sys_days date)
	{
		SetDate(ctrl, date);
	}

	inline std::string GetText(CEdit& ctrl)
	{
		CString str;
		ctrl.GetWindowTextW(str);
		if (str.IsEmpty())
			return ""s;
		auto s = util::from_cstring(str);
		return s;
	}

	inline double GetAmount(CEdit& ctrl)
	{
		auto str = GetText(ctrl);
		if (str.empty())	return 0.0;
		return std::stold(str);
	}


	inline int GetInteger(CEdit& ctrl)
	{
		auto str = GetText(ctrl);
		if (str.empty())	return 0;
		return std::stoi(str);
	}

	inline long GetLong(CEdit& ctrl)
	{
		auto str = GetText(ctrl);
		if (str.empty())	return 0L;
		return std::stol(str);
	}

	inline long long GetLongLong(CEdit& ctrl)
	{
		auto str = GetText(ctrl);
		if (str.empty())	return 0LL;
		return std::stoll(str);
	}

	inline void operator>>(CEdit& ctrl, std::string& s)
	{
		s = GetText(ctrl);
	}
	inline void operator>>(CEdit& ctrl, double& d)
	{
		d = GetAmount(ctrl);
	}
	inline void operator>>(CEdit& ctrl, int& i)
	{
		i = GetInteger(ctrl);
	}
	inline void operator>>(CEdit& ctrl, long& l)
	{
		l = GetLong(ctrl);
	}

	inline void operator>>(CEdit& ctrl, long long& l)
	{
		l = GetLongLong(ctrl);
	}

	inline void operator<<(CEdit& ctrl, std::string s)
	{
		SetText(ctrl, s);
	}

	template<typename T> requires std::is_arithmetic<T>::value
		inline void operator<<(CEdit& ctrl, T d)
	{
		SetAmount(ctrl, d);
	}

	inline void operator<< (CButton& btn, bool check_status)
	{
		btn.SetCheck(check_status);
	}

	inline void operator>> (CButton& btn, bool& check_status)
	{
		check_status = btn.GetCheck();
	}

	template<typename ...Counts>
	bool allNonZero(Counts ... counts) requires (std::is_same_v<Counts, int> && ...)
	{
		return (counts && ...);
	}

	template<size_t N>
	bool anyNonZero(int(&vec)[N])
	{
		return std::any_of(std::begin(vec), std::end(vec), [](int i) { return i != 0; });
	}

}

