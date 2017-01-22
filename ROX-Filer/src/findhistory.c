
#include "config.h"
#include "global.h"

#include "findhistory.h"


void findhistory_new(void)
{
	if (findhistory)
		g_object_unref(G_OBJECT(findhistory));
	findhistory = xml_new(NULL);
	findhistory->doc = xmlNewDoc("1.0");
	xmlDocSetRootElement(findhistory->doc, xmlNewDocNode(findhistory->doc, NULL, "history", NULL));
}

void findhistory_load()
{
	gchar *path;

	/* Update the findhistory, if possible */
	path = choices_find_xdg_path_load("findhistory.xml", PROJECT, SITE);
	if (path)
	{
		XMLwrapper *wrapper;
		wrapper = xml_cache_load(path);
		if (wrapper)
		{
			if (findhistory)
				g_object_unref(findhistory);
			findhistory = wrapper;
		}

		g_free(path);
	}

	if (!findhistory)
		findhistory_new();
}

/* Save the findhistory to a file */
void findhistory_save()
{
	guchar	*save_path;

	save_path = choices_find_xdg_path_save("findhistory.xml", PROJECT, SITE, TRUE);
	if (save_path)
	{
		save_xml_file(findhistory->doc, save_path);
		g_free(save_path);
	}
}

void findhistory_add(const guchar *string)
{
	xmlNode	*entry;
	xmlNode *firstnode;
	int need_reload = 1;

	if (findhistory == NULL)
	{
		findhistory_new();
		need_reload = 0;
	}

	entry = findhistory_find(string, need_reload);
	if (!entry) entry = xmlNewTextChild(xmlDocGetRootElement(findhistory->doc), NULL, "entry", string);
	firstnode = xmlDocGetRootElement(findhistory->doc)->xmlChildrenNode;
	if (firstnode && firstnode != entry)
	{
		xmlUnlinkNode(entry);
		xmlAddPrevSibling(firstnode, entry);
	}
	findhistory_save();
}

xmlNode *findhistory_find(const gchar *string, int need_reload)
{
	xmlNode *node;

	if(need_reload)
		findhistory_load();

	node = xmlDocGetRootElement(findhistory->doc);

	for (node = node->xmlChildrenNode; node; node = node->next)
	{
		gchar *this_string;
		gboolean same;

		if (node->type != XML_ELEMENT_NODE)
			continue;
		if (strcmp(node->name, "entry") != 0)
			continue;

		this_string = xmlNodeListGetString(findhistory->doc, node->xmlChildrenNode, 1);
		if (!this_string)
			continue;

		same = strcmp(string, this_string) == 0;
		xmlFree(this_string);

		if (same)
			return node;
	}

	return NULL;
}

