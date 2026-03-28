# 🐠 Aquarium Intelligent — Système de Surveillance Arduino

![Arduino](https://img.shields.io/badge/Hardware-Arduino_UNO-blue?logo=arduino)
![C++](https://img.shields.io/badge/Language-C%2B%2B-orange)
![Proteus](https://img.shields.io/badge/Simulation-Proteus-green)
![LCD](https://img.shields.io/badge/Display-LCD_16x4-yellow)

> Système embarqué de surveillance automatisée d'un aquarium intelligent — contrôle du pH, du niveau d'eau et de la turbidité en temps réel, avec affichage LCD et gestion automatique de la pompe à eau.

---

## 📌 Contexte & Problématique

Les animaux marins nécessitent un environnement sain et stable pour survivre. Les paramètres critiques comme le **pH**, le **niveau d'eau** et la **turbidité** doivent être surveillés en permanence. Ce projet propose une solution embarquée automatisée qui :

- Élimine la surveillance manuelle
- Réagit automatiquement aux anomalies (niveau d'eau bas → pompe activée)
- Affiche en temps réel l'état de l'aquarium sur un écran LCD

---

## ✨ Fonctionnalités

| Fonctionnalité | Description |
|---|---|
| 🧪 **Mesure du pH** | Lecture analogique via capteur pH Meter V1.0 |
| 💧 **Niveau d'eau** | Mesure par capteur ultrasonique HC-SR04 |
| 🌊 **Turbidité** | Qualité de l'eau via capteur de turbidité |
| 📺 **Affichage LCD** | Écran 16x4 : pH, niveau, turbidité, statut |
| ⚙️ **Pompe automatique** | Activation si niveau d'eau < 30% |
| 🔔 **Statut qualité** | Water Very Clean / Norm Clean / Very Dirty |

---

## 🔌 Composants utilisés

| Composant | Rôle |
|---|---|
| **Arduino UNO** | Microcontrôleur principal |
| **Capteur pH Meter V1.0** | Mesure du pH de l'eau |
| **Capteur ultrasonique HC-SR04** | Mesure du niveau d'eau |
| **Capteur de turbidité** | Mesure de la clarté de l'eau |
| **Écran LCD 16x4** | Affichage des paramètres |
| **Relais + Moteur 220V** | Contrôle de la pompe à eau |

---

## 🖥️ Simulation Proteus

![Simulation Proteus](assets/simulation_proteus.png)

*Simulation complète du circuit sur Proteus — pH : 8.64 | Water : 30% | Turbidity : 19 | Water Norm Clean*

---

## 📐 Logique de fonctionnement

```
[Capteur pH]        → Arduino A1 → Calcul pH (3.5 × Vmoy)
[Capteur Turbidité] → Arduino A0 → Mapping (0–300 NTU)
[HC-SR04]           → Arduino D5/D6 → Distance → Niveau (%)
                                          │
                                    [Arduino UNO]
                                          │
                          ┌───────────────┼───────────────┐
                          ▼               ▼               ▼
                     [LCD 16x4]    [Vérif. niveau]   [Statut eau]
                   pH / Water%    Niveau < 30% ?    Turbidité < 10
                   Turbidité      → Pompe ON/OFF    → Very Clean
                   Statut                           → Norm Clean
                                                    → Very Dirty
```

---

## 💻 Code Arduino

### Seuils & logique

| Paramètre | Condition | Action |
|---|---|---|
| Niveau d'eau | < 30% | Pompe activée automatiquement |
| Turbidité | < 10 | Water Very Clean |
| Turbidité | 10 – 30 | Water Norm Clean |
| Turbidité | > 30 | Water Very Dirty |

### Pins utilisées

| Pin | Composant | Mode |
|---|---|---|
| A0 | Capteur turbidité | INPUT analogique |
| A1 | Capteur pH | INPUT analogique |
| D5 | HC-SR04 TRIG | OUTPUT |
| D6 | HC-SR04 ECHO | INPUT |
| D7 | Relais pompe | OUTPUT |
| D8–D13 | LCD 16x4 | OUTPUT |

---

## 🗂️ Structure du projet

```
📦 smart-aquarium/
├── 📁 assets/
│   └── simulation_proteus.png   # Capture de la simulation Proteus
├── 📄 aquarium.ino              # Code source Arduino principal
├── 📄 aquarium.pdsprj           # Fichier simulation Proteus
└── 📄 README.md
```

---

## 🚀 Comment tester

### Sur Proteus (simulation)
1. Ouvre le fichier `aquarium.pdsprj` avec Proteus
2. Lance la simulation (bouton ▶️)
3. Observe les valeurs sur l'écran LCD simulé

### Sur Arduino réel
1. Installe [Arduino IDE](https://www.arduino.cc/en/software)
2. Ouvre `aquarium.ino`
3. Branche ton Arduino UNO via USB
4. Sélectionne le bon port COM
5. Clique sur **Téléverser** ✅

---

## 🎓 Contexte académique

| | |
|---|---|
| **Établissement** | École Supérieure de Technologie d'Oujda (ESTO) |
| **Filière** | Génie Informatique Embarquée |
| **Année** | 2022 – 2024 |

---

## 👩‍💻 Auteure

**Jihane Bouras**
🔗 [LinkedIn](https://linkedin.com/in/jihane-bouras-74896427a) • 📧 jihane.brs123@gmail.com

---

## 🔮 Perspectives

- 📱 Ajout d'une interface mobile (Bluetooth / WiFi)
- 🌡️ Capteur de température de l'eau
- 💡 Contrôle automatique de l'éclairage
- 📊 Historique des données sur carte SD

---

## 📄 Licence

Projet académique — ESTO Oujda 2022–2024.
