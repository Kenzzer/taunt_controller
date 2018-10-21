/**
 * ==============================================================================
 * Taunt Controller
 * Copyright (C) 2018 Benoist3012
 * ==============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#if defined _taunt_controller_included
 #endinput
#endif
#define _taunt_controller_included

/**
 * Called whenever the function CTFPlayer::PlayTauntSceneFromItem(CEconItemView *pTauntItem) is used.
 *
 * @param result		The value to return if the function is overridden.
 * @return				Return anything but Plugin_Continue to override with the value from 'result', use Plugin_Stop to prevent the server code from running.
 */
forward Action CTFPlayer_PlayTauntSceneFromItem(int iClient, int iTauntIndex, bool &bTauntSuccess);


/**
 * Do not edit below this line!
 */
public Extension __ext_tauntcontroller = 
{
	name = "Taunt Controller",
	file = "taunt_controller.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};