﻿#pragma once
#include "Model.DataTier.h"

namespace Model
{
	class PersistentCollections
	{
	public:
		static std::vector<std::shared_ptr<StatementLine>>
			get_statement_lines_for(const std::string& account, date::sys_days statement_date);

	};
}
