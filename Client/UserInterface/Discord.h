#include "StdAfx.h"
#include "PythonCharacterManager.h"
#include "PythonBackground.h"
#include "PythonPlayer.h"
#include "PythonGuild.h"
#include "fmt/fmt.h"

namespace Discord
{
	constexpr auto DiscordClientID = "790361984922026044";

	using DCDATA = std::pair<std::string, std::string>;

	inline void ReplaceStringInPlace(std::string& subject, const std::string& search,
		const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
	}
	inline void capitalizeWord(std::string& str)
	{
		bool canCapitalize = true;
		for (auto& c : str)
		{
			if (isalpha(c))
			{
				if (canCapitalize)
				{
					c = std::toupper(c);
					canCapitalize = false;
				}
			}
			else
				canCapitalize = true;
		}
	}

	/*NAME*/
	inline DCDATA GetNameData()
	{
		/*Map Name*/
		auto WarpName = std::string(CPythonBackground::Instance().GetWarpMapName());

		//atlasinfo.txt
		static const std::map<std::string, std::string> DCmapname{
			{ "metin2_map_a1", "Yongan" },
			{ "metin2_map_b1", "Joan" },
			{ "metin2_map_c1", "Pyungmoo" },
			{ "metin2_map_a1_xmas", "Yongan Xmas" },
			{ "metin2_map_b1_xmas", "Joan Xmas" },
			{ "metin2_map_c1_xmas", "Pyungmoo Xmas" },
		};

		if (!DCmapname.count(WarpName))
		{
			ReplaceStringInPlace(WarpName, "season1/", "");
			ReplaceStringInPlace(WarpName, "season2/", "");
			ReplaceStringInPlace(WarpName, "metin2_map_", "");
			ReplaceStringInPlace(WarpName, "metin2_", "");
			ReplaceStringInPlace(WarpName, "plechito_", "");
			ReplaceStringInPlace(WarpName, "_", " ");
			capitalizeWord(WarpName);
		}
		auto MapName = "Location: " + (DCmapname.count(WarpName) ? DCmapname.at(WarpName) : WarpName);

		/*CH Name*/
		std::string GuildName;
		CPythonGuild::Instance().GetGuildName(CPythonPlayer::Instance().GetGuildID(), &GuildName);
		auto CHName = fmt::format("{} Lv{} {}", CPythonPlayer::Instance().GetName(), CPythonPlayer::Instance().GetStatus(POINT_LEVEL), GuildName);

		return { MapName, CHName };
	}

	/*RACE*/
	inline DCDATA GetRaceData()
	{
		auto pInstance = CPythonCharacterManager::Instance().GetMainInstancePtr();
		if (!pInstance)
			return { "","" };

		auto RACENUM = pInstance->GetRace();

		/*Image*/
		auto RaceImage = "race_" + std::to_string(RACENUM);

		/*Name*/
		auto RaceName = "Warrior";
		switch (RACENUM)
		{
		case NRaceData::JOB_ASSASSIN:
		case NRaceData::JOB_ASSASSIN + 4:
			RaceName = "Assassin";
			break;
		case NRaceData::JOB_SURA:
		case NRaceData::JOB_SURA + 4:
			RaceName = "Sura";
			break;
		case NRaceData::JOB_SHAMAN:
		case NRaceData::JOB_SHAMAN + 4:
			RaceName = "Shaman";
			break;
#if defined(ENABLE_WOLFMAN_CHARACTER)
		case NRaceData::JOB_WOLFMAN + 4:
			RaceName = "Lycan";
#endif
		}
		return { RaceImage , RaceName };
	}

	/*EMPIRE*/
	inline DCDATA GetEmpireData()
	{
		auto pInstance = CPythonCharacterManager::Instance().GetMainInstancePtr();
		if (!pInstance)
			return { "","" };

		auto EmpireID = pInstance->GetEmpireID();

		/*Image*/
		auto EmpireImage = "empire_" + std::to_string(EmpireID);

		/*Name*/
		auto EmpireName = "Shinsoo";
		switch (EmpireID)
		{
		case 2:
			EmpireName = "Chunjo";
			break;
		case 3:
			EmpireName = "Jinno";
		}
		return { EmpireImage, EmpireName };
	}
}
//martysama0134's 2022
