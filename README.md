# Agile Humanities DiRT Module

The Agile DiRT Module works in conjunction with the Agile DHCommons Module to allow meaningful exchange of information between the DiRT and DHCommons websites. Both modules are complementary, with each to be installed on its respective website. Each module publishes and subscribes. Each operates independently and does not require the other to be installed, but they are designed for simultaneous use. Both modules are written for Drupal 7.

It is assumed that API-Key authentication will be used to restrict access to published data. If authentication is used, the Drupal Services API Key Authentication module must be installed and enabled. If access is to be left open, all further references to API keys may be ignored.

The DiRT module is comprised of two parts&mdash;one to publish data associated with individual tools defined by the DiRT ‘item’ content type, and another to read and present published data defined by the DHCommons ‘project’ content type.

## Preparation

Install and enable the Agile Humanities DiRT Features Module. This indicates to the installer all required sub-modules and defines the necessary content types. This step may be omitted if your site is already configured with a standard DiRT installation.

Install and enable the Agile Humanities DiRT Module.

Create a Drupal role called **rest user**, and give members of that role access to all permissions listed under Services.

Create a user called **RestUser**.  This fictional user exists only for configuration purposes. Credentials are unimportant. Assign this new user the role of **rest user**.

## Required Drupal 7 Modules
- Services
- Services Entity API
- Services API Key Authentication (optional)

## Configure publishing

The administrator of the site must set up a REST endpoint.

Navigate to **admin/structure/services** to add an endpoint.

Click on the **API Key Settings** tab, then select **rest user** as the user role.

Click List, then **+Add** to navigate to **admin/structure/services/add**

Enter a machine-readable name for the endpoint, select **REST** as the server, and enter a path. The names chosen for the endpoint and path are not significant. Use **rest** for both the machine-readable name and the path of the endpoint.

Check **API Key Authentication**. The other boxes should remain unchecked.

**_Save!_**

Edit the rest endpoint by clicking **Edit Resources**. In the **Server** tab, check all boxes.

**_Save!_**

Under **Authentication**, select **RestUser**as your user, and enter an API key. This key can be anything; in ourtest example we’ll use **agile_key.**

**_Save!_**

Under **Resources** check **item**. Enter **tool** in the alias textfield opposite **item**.

Test the endpoint by entering `<your site name>/rest`

You should see a message indicating that the endpoint has been  set up properly.

Test authentication by entering `<your site name>/rest/tool/fetch`

You should be asked for a password. Clicking **Cancel** should give an **Unauthorized** access message.

If you’ve created a few full populated item nodes, the following should bring back sample data:

`<your site name>/rest/tool/fetch?api-key=agile_key`

Your site is now ready to publish via REST to a properly configured subscriber site.

To configure the connection, your subscriber site must know your site’s url, API key, REST path, and alias. The administrator of the DiRT site must make this information known to the administrator of the Project site that consumes the DiRT RESTful data.

## Configure DiRT Admin

Navigate to **Home/Administration/Configuration/Web services/DirtTools Config**

Access values provided by the administrator of the DHCommons website must be entered here.

Enter the API key, project site url, project site name, rest path, alias and taxonomy as supplied to you by the project site administrator. These values are mandatory and must be typed in exactly.

Two additional configuration options allow results to be sorted either by age or title, and the maximum number of displayed results.

## Configure subscribing

Navigate to **admin/config/services/dirt**

The Agile DHCommons Module has a similar configuration to the Agile DiRT Module. From the DHCommons administrator, you will need to obtain the API key, site url, REST path, alias, and taxonomy. Enter these values, and your site should now be able to retrieve project information from DHCommons.

Check either Timestamp or Title for the sort order of returned results.

The connection can be tested by entering

`<dhcommons url>/<rest path>/<alias>/fetch?api-key=<supplied key>`

## Configure display

The DiRT site displays its tool information using Drupal’s Display Suite. A tab must be configured for the ‘item’ content type using the Display Suite management interface.

### Create a new tab item  

- Navigate to any DiRT tool, and click the **Manage Display** tab
- Enter **Project** in the textfield immediately below **Add new group**
- Enter **Project** in the **group_textfield/**
- Select **Horizontal tab item** from the **Fieldset** dropdown

**_Save!_**

Your new tab will now show up as the last entry under **Disabled** on the configuration page. Drag the element up into the active area, change its dropdown from **disabled** to **content**. The element can be dragged vertically and horizontally. It should appear after all the sub-elements of **Description** and have the same vertical indentation as **Description**.

### Create the block element

- Navigate to any DiRT tool and click the **Manage Display** tab
- Click **Custom Fields** at the bottom of the configuration page
- Click **Add a block field**
- Enter **Projects** as label and check **Node** under entities
- From the **Block** dropdown select **DHCommons Projects**
- From the **Layout** dropdown select  **Show only block content**

**_Save!_**

Returning to the previous configuration screen will show your new **Projects** field listed under **disabled**. Use the handle to drag the field until it is located horizontally immediately under your previously created **Project** tab and indented one level to the right.

Your configuration should now be ready.
