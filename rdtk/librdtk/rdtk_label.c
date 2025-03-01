/**
 * RdTk: Remote Desktop Toolkit
 *
 * Copyright 2014 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <winpr/assert.h>

#include <rdtk/config.h>

#include "rdtk_font.h"

#include "rdtk_label.h"

int rdtk_label_draw(rdtkSurface* surface, uint16_t nXDst, uint16_t nYDst, uint16_t nWidth,
                    uint16_t nHeight, WINPR_ATTR_UNUSED rdtkLabel* label, const char* text,
                    WINPR_ATTR_UNUSED uint16_t hAlign, WINPR_ATTR_UNUSED uint16_t vAlign)
{
	uint16_t offsetX = 0;
	uint16_t offsetY = 0;
	uint16_t textWidth = 0;
	uint16_t textHeight = 0;

	WINPR_ASSERT(surface);

	rdtkEngine* engine = surface->engine;
	rdtkFont* font = engine->font;

	rdtk_font_text_draw_size(font, &textWidth, &textHeight, text);

	if ((textWidth > 0) && (textHeight > 0))
	{
		offsetX = 0;
		offsetY = 0;

		if (textWidth < nWidth)
			offsetX = ((nWidth - textWidth) / 2);

		if (textHeight < nHeight)
			offsetY = ((nHeight - textHeight) / 2);

		rdtk_font_draw_text(surface, nXDst + offsetX, nYDst + offsetY, font, text);
	}

	return 1;
}

rdtkLabel* rdtk_label_new(rdtkEngine* engine)
{
	WINPR_ASSERT(engine);
	rdtkLabel* label = (rdtkLabel*)calloc(1, sizeof(rdtkLabel));

	if (!label)
		return NULL;

	label->engine = engine;

	return label;
}

void rdtk_label_free(rdtkLabel* label)
{
	free(label);
}

int rdtk_label_engine_init(rdtkEngine* engine)
{
	WINPR_ASSERT(engine);
	if (!engine->label)
	{
		engine->label = rdtk_label_new(engine);
	}

	return 1;
}

int rdtk_label_engine_uninit(rdtkEngine* engine)
{
	WINPR_ASSERT(engine);
	if (engine->label)
	{
		rdtk_label_free(engine->label);
		engine->label = NULL;
	}

	return 1;
}
