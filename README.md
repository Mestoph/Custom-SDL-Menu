# Custom-SDL-Menu
Custom SDL Menu is a menu that is compatible with Windows and Linux for running various commands. It is fully customizable.

The primary goal of this project was to create a start menu on a Raspberry Pi.

# Preview
![Alt text](https://github.com/Mestoph/Custom-SDL-Menu/blob/main/resources/screenshots/preview.png "Optional title")

# Settings
Here is an example of the menu configuration. It has no limit on the number of submenus, but it will only display a maximum of 10 buttons per page. This limit can be modified in the "constants.h" file.

```json
{
  "menu": {
    "bg_image": "bg.jpg",
    "bg_color": "#000000",
    "t_color": "#FFFFFF",
    "s_color": "#FF0000",
    "title": {
      "color": "#00FF00",
      "text": "Menu principal"
    },
    "buttons": [
      {
        "t_color": "#FFFFFF",
        "s_color": "#FF0000",
        "text": "Jouer 1",
        "menu": {
          "title": {
            "color": "#00FF00",
            "text": "Sous-menu Jouer 1"
          },
          "buttons": [
            {
              "text": "Nouvelle partie 1",
              "action": "new"
            },
            {
              "text": "Charger partie 1",
              "action": "load"
            },
            {
              "text": "Retour",
              "action": "back"
            }
          ]
        }
      },
      {
        "t_color": "#FFFFFF",
        "s_color": "#FF0000",
        "text": "Jouer 2",
        "menu": {
          "title": {
            "color": "#00FF00",
            "text": "Sous-menu Jouer 2"
          },
          "buttons": [
            {
              "text": "Nouvelle partie 2",
              "action": "new"
            },
            {
              "text": "Charger partie 2",
              "action": "load"
            },
            {
              "text": "Retour 2",
              "action": "back"
            }
          ]
        }
      },
      {
        "t_color": "#FFFFFF",
        "s_color": "#FF0000",
        "text": "Jouer 3",
        "menu": {
          "title": {
            "color": "#00FF00",
            "text": "Sous-menu Jouer 3"
          },
          "buttons": [
            {
              "text": "Nouvelle partie 3",
              "action": "new"
            },
            {
              "text": "Charger partie 3",
              "action": "load"
            },
            {
              "text": "Retour 3",
              "action": "back"
            }
          ]
        }
      },
      {
        "text": "Quitter",
        "action": "end"
      }
    ]
  }
}
```
