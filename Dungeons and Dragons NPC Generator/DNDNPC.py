# Dylan Vidal
# ShellHacks 2023
# Dungeons and Dragons NPC Generator
# DNDNPC.py
# Uses TK to form a User Interface to generate a random NPC for a Dungeons and Dragons Campaign
# Prompted using GPT-3.5

# Import Modules
from tkinter import *
from tkinter import font
from tkinter import ttk
import random
import math

def genName():
    file = open("name.txt", "r")
    line = next(file)
    for num, aline in enumerate(file, 2):
        if random.randrange(num):
            continue
        line = aline
    file.close()
    return line.strip()


def genRacial():
    race_info = [
        {"Race": "Aarakockra", "Low Age": 3, "High Age": 30, "Low Height": 60, "High Height": 72},
        {"Race": "Aasimar", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Bugbear", "Low Age": 16, "High Age": 80, "Low Height": 72, "High Height": 96},
        {"Race": "Centaur", "Low Age": 15, "High Age": 100, "Low Height": 72, "High Height": 84},
        {"Race": "Changeling", "Low Age": 20, "High Age": 80, "Low Height": 60, "High Height": 72},
        {"Race": "Dragonborn", "Low Age": 15, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Chromatic Dragonborn", "Low Age": 15, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Gem Dragonborn", "Low Age": 15, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Metallic Dragonborn", "Low Age": 15, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Dwarves", "Low Age": 50, "High Age": 350, "Low Height": 36, "High Height": 48},
        {"Race": "Duergar", "Low Age": 50, "High Age": 350, "Low Height": 36, "High Height": 48},
        {"Race": "Hill Dwarf", "Low Age": 50, "High Age": 350, "Low Height": 36, "High Height": 48},
        {"Race": "Mountain Dwarf", "Low Age": 50, "High Age": 350, "Low Height": 36, "High Height": 48},
        {"Race": "Elves", "Low Age": 100, "High Age": 750, "Low Height": 60, "High Height": 72},
        {"Race": "Astral Elf", "Low Age": 100, "High Age": 750, "Low Height": 60, "High Height": 72},
        {"Race": "Drow (Dark Elf)", "Low Age": 100, "High Age": 750, "Low Height": 60, "High Height": 72},
        {"Race": "Eladrin", "Low Age": 100, "High Age": 750, "Low Height": 60, "High Height": 72},
        {"Race": "High Elf", "Low Age": 100, "High Age": 750, "Low Height": 60, "High Height": 72},
        {"Race": "Sea Elf", "Low Age": 100, "High Age": 750, "Low Height": 60, "High Height": 72},
        {"Race": "Shadar-Kai", "Low Age": 100, "High Age": 750, "Low Height": 60, "High Height": 72},
        {"Race": "Wood Elf", "Low Age": 100, "High Age": 750, "Low Height": 60, "High Height": 72},
        {"Race": "Fairy", "Low Age": 20, "High Age": 200, "Low Height": 48, "High Height": 72},
        {"Race": "Firbolg", "Low Age": 30, "High Age": 500, "Low Height": 72, "High Height": 96},
        {"Race": "Genasi", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Air Genasi", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Earth Genasi", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Fire Genasi", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Water Genasi", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Giff", "Low Age": 18, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Gith", "Low Age": 18, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Githyanki", "Low Age": 18, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Githzerai", "Low Age": 18, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Gnomes", "Low Age": 20, "High Age": 500, "Low Height": 36, "High Height": 48},
        {"Race": "Autognome", "Low Age": 20, "High Age": 500, "Low Height": 36, "High Height": 48},
        {"Race": "Deep Gnome (Svirfneblin)", "Low Age": 20, "High Age": 500, "Low Height": 36, "High Height": 48},
        {"Race": "Forest Gnome", "Low Age": 20, "High Age": 500, "Low Height": 36, "High Height": 48},
        {"Race": "Rock Gnome", "Low Age": 20, "High Age": 500, "Low Height": 36, "High Height": 48},
        {"Race": "Goblin", "Low Age": 10, "High Age": 60, "Low Height": 36, "High Height": 48},
        {"Race": "Goliath", "Low Age": 18, "High Age": 100, "Low Height": 72, "High Height": 96},
        {"Race": "Grung", "Low Age": 18, "High Age": 80, "Low Height": 24, "High Height": 48},
        {"Race": "Hadozee", "Low Age": 15, "High Age": 60, "Low Height": 60, "High Height": 84},
        {"Race": "Half-Elf", "Low Age": 20, "High Age": 180, "Low Height": 60, "High Height": 72},
        {"Race": "Half-Orc", "Low Age": 14, "High Age": 75, "Low Height": 60, "High Height": 84},
        {"Race": "Halflings", "Low Age": 20, "High Age": 250, "Low Height": 24, "High Height": 36},
        {"Race": "Ghostwise Halfling", "Low Age": 20, "High Age": 250, "Low Height": 24, "High Height": 36},
        {"Race": "Lightfoot Halfling", "Low Age": 20, "High Age": 250, "Low Height": 24, "High Height": 36},
        {"Race": "Stout Halfling", "Low Age": 20, "High Age": 250, "Low Height": 24, "High Height": 36},
        {"Race": "Harengon", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Hobgoblin", "Low Age": 20, "High Age": 80, "Low Height": 60, "High Height": 72},
        {"Race": "Human", "Low Age": 18, "High Age": 100, "Low Height": 48, "High Height": 84},
        {"Race": "Kalashtar", "Low Age": 20, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Kender", "Low Age": 20, "High Age": 100, "Low Height": 36, "High Height": 48},
        {"Race": "Kenku", "Low Age": 12, "High Age": 60, "Low Height": 48, "High Height": 60},
        {"Race": "Kobold", "Low Age": 6, "High Age": 120, "Low Height": 24, "High Height": 36},
        {"Race": "Leonin", "Low Age": 18, "High Age": 100, "Low Height": 72, "High Height": 84},
        {"Race": "Lizardfolk", "Low Age": 14, "High Age": 60, "Low Height": 60, "High Height": 84},
        {"Race": "Locathah", "Low Age": 10, "High Age": 80, "Low Height": 48, "High Height": 72},
        {"Race": "Loxodon", "Low Age": 50, "High Age": 450, "Low Height": 72, "High Height": 96},
        {"Race": "Minotaur", "Low Age": 20, "High Age": 150, "Low Height": 72, "High Height": 84},
        {"Race": "Orc", "Low Age": 12, "High Age": 80, "Low Height": 60, "High Height": 84},
        {"Race": "Owlin", "Low Age": 15, "High Age": 80, "Low Height": 60, "High Height": 72},
        {"Race": "Plasmoids", "Low Age": 10, "High Age": 100, "Low Height": 48, "High Height": 72},
        {"Race": "Satyr", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Shifter", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Simic Hybrid", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Tabaxi", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Thri-Kreen", "Low Age": 5, "High Age": 30, "Low Height": 72, "High Height": 84},
        {"Race": "Tiefling", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Tortle", "Low Age": 15, "High Age": 60, "Low Height": 48, "High Height": 60},
        {"Race": "Triton", "Low Age": 18, "High Age": 200, "Low Height": 60, "High Height": 72},
        {"Race": "Vedalken", "Low Age": 20, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Verdan", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        {"Race": "Warforged", "Low Age": 2, "High Age": 30, "Low Height": 60, "High Height": 84},
        {"Race": "Yuan-Ti Pureblood", "Low Age": 18, "High Age": 100, "Low Height": 60, "High Height": 72},
        # Add more races as needed
    ]

    racial = random.choice(race_info)
    return racial


def generate(raceStr, ageStr, heightStr, hairStr, eyesStr, buildStr, fashionStr, firstStr, lastStr, classStr, gStr, lvlStr, algnStr, quirkStr):
    # Gather Racial Information from List
    racial = genRacial()
    
    # Set Race
    race = racial["Race"]
    raceStr.set("Race: " + race)

    # Generate Age from Values
    lowAge = int(racial["Low Age"])
    highAge = int(racial["High Age"])
    age = str(random.randint(lowAge, highAge))
    ageStr.set("Age: " + age)

    # Generate Height (in Inches) from Values, and Format
    lowHeight = int(racial["Low Height"])
    highHeight = int(racial["High Height"])
    height = random.randint(lowHeight, highHeight)
    heightFt = math.floor(height/12)
    heightIn = height % 12
    finalHeight = str(heightFt) + "'" + str(heightIn) + "\""
    heightStr.set("Height: " + finalHeight)

    # Generate Hair
    hairColors = ["Black", "Brown", "Dark Brown", "Light Brown", "Golden Brown", "Chestnut Brown",
    "Auburn", "Red", "Strawberry Blonde", "Blonde", "Platinum Blonde", "Dirty Blonde",
    "Ash Blonde", "Honey Blonde", "Sandy Blonde", "Silver", "Gray", "Salt and Pepper",
    "White", "Blue", "Navy Blue", "Teal", "Green", "Emerald Green", "Forest Green",
    "Olive Green", "Mint Green", "Pink", "Hot Pink", "Bubblegum Pink", "Lavender",
    "Purple", "Violet", "Indigo", "Lilac", "Orchid", "Orchid Pink", "Peach", "Copper",
    "Mahogany", "Burgundy", "Maroon", "Wine", "Rust", "Cinnamon", "Amber", "Honey",
    "Tawny", "Platinum", "Lavender Gray", "Steel Gray", "Charcoal", "Rainbow", "Ombre",
    "Two-Tone", "Highlights", "Lowlights", "Balayage", "Unicorn", "Mermaid", "Neon",
    "Pastel", "Iridescent", "Opal", "Silver Fox", "Natural"]
    hair = random.choice(hairColors)
    hairStr.set("Hair: " + hair)

    # Generate Eyes
    eyeColors = [
    "Amber", "Blue", "Brown", "Green", "Gray", "Hazel", "Black", "Red", "Violet",
    "Aqua", "Teal", "Turquoise", "Gold", "Silver", "Copper", "Topaz", "Emerald",
    "Sapphire", "Ruby", "Opal", "Onyx", "Peridot", "Aquamarine", "Jade", "Bronze",
    "Chestnut", "Olive", "Lavender", "Indigo", "Honey", "Pink", "Platinum", "White",
    "Mixed", "Multicolored", "Other"]
    eyes = random.choice(eyeColors)
    eyesStr.set("Eyes: " + eyes)

    # Generate Build
    builds = [
    "Muscular", "Skinny", "Cunning", "Bulky", "Lean", "Athletic",
    "Tall", "Short", "Average", "Stocky", "Chubby", "Slender", "Hulking",
    "Compact", "Stout", "Lithe", "Robust", "Gangly", "Toned", "Gnarled"]
    build = random.choice(builds)
    buildStr.set("Build: " + build)

    # Generate Fashion Description
    fashionDescriptions = [
        "Mystical and enchanted in robes adorned with arcane symbols.",
        "Warrior-like with leather armor and metal gauntlets.",
        "Regal and royal in a velvet cloak and crown adorned with gemstones.",
        "Steampunk-inspired with gears and cogs incorporated into the outfit.",
        "Elven elegance with flowing silk robes and intricate leaf patterns.",
        "Mage-like with a robe adorned with celestial symbols and a wizard's hat.",
        "Barbarian fierceness with fur-lined armor and tribal tattoos.",
        "Dwarven craftsmanship with finely detailed metalwork and sturdy boots.",
        "Ranger attire with a hooded cloak and camouflage accessories.",
        "Rogue-inspired with dark clothing and hidden pockets for secrets.",
        "Knightly in shining armor adorned with noble emblems.",
        "Sorcerous with a cloak of shimmering stars and a crystal staff.",
        "Beastmaster attire with fur-lined accessories and totemic jewelry.",
        "Paladin's regalia with polished plate armor and a radiant sword.",
        "Fey-like in ethereal gowns and wreaths of wildflowers.",
        "Druidic in earth-toned robes adorned with natural elements.",
        "Necromancer's attire with tattered black robes and bone jewelry.",
        "Pirate-inspired with a tricorn hat and a weathered eyepatch.",
        "Bardic with colorful garments and a lute slung over the shoulder.",
        "Monastic in simple robes and a serene demeanor.",
        "Thief-like with dark attire and a mask concealing identity.",
        "Celestial with celestial-inspired clothing and a halo-like headpiece.",
        "Huntsman's attire with camouflage and animal hide accessories.",
        "Shadowy in dark cloaks and a sense of mystery.",
        "Artisan's attire with smock and tools for crafting.",
        "Ethereal in diaphanous garments that seem to float.",
        "Sylvan with forest-inspired attire and leafy accessories.",
        "Dragonlord's regalia with dragon-scale armor and a fiery presence.",
        "Nomadic in layered clothing and desert-inspired accessories.",
        "Elemental with attire representing the four elements.",
        "Enchanter's robes adorned with runes and enchanted trinkets.",
        "Oracle-like with flowing robes and a mysterious aura.",
        "Alchemist's attire with vials and potions at the ready.",
        "Serpentine with snake-themed accessories and scaleskin patterns.",
        "Chronomancer's robes adorned with hourglasses and time-related symbols.",
        "Tribal in animal pelts and tribal markings.",
        "Celestial with attire adorned with celestial bodies and wings.",
        "Sorcerer's attire with swirling patterns and a staff of power.",
        "Inquisitor's robes with a stern demeanor and religious symbols.",
        "Gnomish inventor attire with gadgets and tinkering tools.",
        "Warlock's attire with eldritch symbols and an eerie presence.",
        "Elemental with attire representing the four elements.",
        "Futuristic with metallic clothing and high-tech accessories.",
        "Draconic in dragon-themed armor and scaleskin patterns.",
        "Spellslinger attire with a wizard's hat and spellbook.",
        "Merchant's clothing with pockets for trade goods and a merchant's charm.",
        "Mystic with attire adorned with crystal orbs and mystic symbols.",
        "Beastmaster attire with furs and totemic accessories.",
        "Inquisitor's robes with a stern demeanor and religious symbols.",
        "Tribal in animal pelts and tribal markings."]
    fashion = random.choice(fashionDescriptions)
    fashionStr.set("Fashion: " + fashion)

    # Generate First Name
    firstName = genName()
    firstStr.set("First: " + firstName)

    # Generate Last Name
    lastName = genName()
    lastStr.set("Last: " + lastName)

    # Generate Gender
    genderList = ["Male", "Female", "Non-Binary", "Construct"]
    gender = random.choice(genderList)
    gStr.set("Gender: " + gender)

    # Generate Level
    levelRange = ["1", "2", "3", "4", "5", "6"]
    level = random.choice(levelRange)   
    lvlStr.set("Level: " + level)

    # Generate Alignment
    alignmentList = [
        "Chaotic Neutral",
        "Chaotic Evil", 
        "Chaotic Good",
        "True Neutral",
        "Neutral Good",
        "Neutral Evil",
        "Lawful Good",
        "Lawful Neutral",
        "Lawful Evil"
    ]     
    alignment = random.choice(alignmentList)
    algnStr.set("Alignment: " + alignment)

    # Generate Class and Subclass
    classesAndSubclasses = [
    ["Artificer", ["Alchemist", "Artillerist", "Battle Smith"]],
    ["Barbarian", ["Path of the Ancestral Guardian", "Path of the Battlerager", "Path of the Beast",
                   "Path of the Berserker", "Path of the Storm Herald", "Path of the Totem Warrior",
                   "Path of the Wild Soul"]],
    ["Bard", ["College of Creation", "College of Eloquence", "College of Glamour", "College of Lore",
              "College of Swords", "College of Valor", "College of Whispers"]],
    ["Cleric", ["Arcana Domain", "Death Domain", "Forge Domain", "Grave Domain", "Knowledge Domain",
                "Life Domain", "Light Domain", "Nature Domain", "Order Domain", "Peace Domain",
                "Tempest Domain", "Trickery Domain", "Twilight Domain", "War Domain"]],
    ["Druid", ["Circle of Dreams", "Circle of Spores", "Circle of Stars", "Circle of the Shepherd",
               "Circle of the Land", "Circle of the Moon"]],
    ["Fighter", ["Arcane Archer", "Banneret", "Battle Master", "Cavalier", "Champion", "Echo Knight",
                 "Eldritch Knight", "Psi Knight", "Rune Knight", "Samurai"]],
    ["Monk", ["Way of the Astral Self", "Way of the Drunken Master", "Way of Mercy", "Way of the Open Hand",
               "Way of the Shadow", "Way of the Sun Soul", "Way of the Four Elements", "Way of the Kensei"]],
    ["Paladin", ["Oath of the Ancients", "Oath of Conquest", "Oath of the Crown", "Oath of Devotion",
                 "Oath of Redemption", "Oath of Vengeance"]],
    ["Ranger", ["Beast Master", "Fey Wanderer", "Gloom Stalker", "Horizon Walker", "Hunter", "Monster Slayer",
                "Swarmkeeper"]],
    ["Rogue", ["Arcane Trickster", "Assassin", "Inquisitive", "Mastermind", "Phantom", "Scout", "Soulknife",
               "Swashbuckler", "Thief"]],
    ["Sorcerer", ["Aberrant Mind", "Clockwork Soul", "Divine Soul", "Draconic Bloodline", "Shadow Magic",
                   "Storm Sorcery", "Wild Magic"]],
    ["Warlock", ["The Archfey", "The Celestial", "The Fathomless", "The Fiend", "The Genie", "The Great Old One",
                   "The Hexblade", "The Undying"]],
    ["Wizard", ["Bladesinging", "Chronurgy Magic", "Graviturgy Magic", "School of Abjuration", "School of Conjuration",
                 "School of Divination", "School of Enchantment", "School of Evocation", "School of Illusion",
                 "School of Necromancy", "School of Transmutation", "War Magic"]]]
    charClassList = random.choice(classesAndSubclasses)
    charClass = charClassList[0]
    subClass = random.choice(charClassList[1])
    classStr.set("Class: " + subClass + " " + charClass)

    # Generate Quirk
    quirks = [
        "Always carries a small pet lizard on their shoulder.",
        "Obsessed with collecting rare and exotic spices.",
        "Has a habit of rhyming everything they say.",
        "Refuses to wear shoes, even in the coldest of weather.",
        "Believes they can communicate with plants and talks to them regularly.",
        "Compulsively rearranges objects on tables and shelves.",
        "Carries around a pocket-sized book of bad jokes.",
        "Speaks in a thick accent from a distant land, even though they're local.",
        "Has an irrational fear of the color orange.",
        "Can't resist petting every stray animal they come across.",
        "Constantly twirls a lock of hair when lost in thought.",
        "Refuses to eat anything green, claiming it's an unlucky color.",
        "Insists on wearing a monocle, even if they have perfect vision.",
        "Carves intricate designs into their walking stick.",
        "Has a tendency to fall asleep in the middle of conversations.",
        "Claims to have a secret treasure map tattooed on their back.",
        "Always carries a tiny umbrella, regardless of the weather.",
        "Refers to themselves in the third person.",
        "Writes poetry about the most mundane things in life.",
        "Is convinced that they can talk to animals and often has lengthy conversations with squirrels.",
        "Refuses to touch anything made of metal.",
        "Is convinced that they're being followed by invisible spirits.",
        "Carries a small pouch of glitter and tosses it in the air for dramatic effect.",
        "Believes they have a lucky coin and flips it for every decision.",
        "Has an extensive collection of exotic hats and wears a different one each day.",
        "Is an avid birdwatcher and can identify hundreds of bird species by their calls.",
        "Has a habit of using overly complex vocabulary in everyday speech.",
        "Refuses to walk on cracks in the pavement, fearing bad luck.",
        "Claims to have a 'lucky' rock that they consult for advice.",
        "Believes they are cursed and constantly looks for signs of impending doom.",
        "Always carries a small jar of fireflies for 'mood lighting'.",
        "Has an irrational fear of mirrors and avoids looking into them.",
        "Collects unusual and rare coins from all over the world.",
        "Has a habit of breaking into song and dance at the most inappropriate times.",
        "Believes they are a distant royal relative and insists on being addressed as 'Your Highness'.",
        "Is a strict vegetarian and lectures others about the benefits of a meat-free diet.",
        "Carries around a small sketchbook and draws caricatures of people they meet.",
        "Refers to everyone as 'my dear' or 'darling', regardless of their relationship.",
        "Claims to have a guardian angel that watches over them at all times.",
        "Is obsessed with solving riddles and frequently poses them to others.",
        "Has an uncanny ability to mimic the voices of famous people.",
        "Refuses to walk through doorways without performing a little dance.",
        "Carries a small vial of 'magic dust' that they sprinkle for good luck.",
        "Believes they can communicate with the stars and often stargazes for hours.",
        "Has a pet parrot that repeats everything they say.",
        "Is convinced they can speak to ghosts and often holds séances.",
        "Always wears mismatched socks and claims it's a fashion statement.",
        "Carries a small magnifying glass and inspects everything closely.",
        "Has a fear of water and refuses to swim or bathe.",
        "Claims to have a 'lucky' feather that they keep tucked behind their ear.",
        "Is a firm believer in conspiracy theories and frequently shares them with others.",
        "Always carries a small bag of marbles and enjoys playing with them absentmindedly.",
        "Believes they are a time traveler from the future and talks about future inventions.",
        "Has an obsession with collecting antique doorknobs.",
        "Refuses to eat anything that has been cooked by someone else.",
        "Carries a small pouch of dried herbs and claims they have healing powers.",
        "Believes they have a 'sixth sense' and can predict the future.",
        "Is convinced that they are a master of disguise and often wears elaborate costumes.",
        "Has an unusual fascination with counting things and is always tallying objects.",
        "Claims to have a 'lucky' coin that they must flip before making any decisions.",
        "Always carries a small jar of lightning bugs and releases them at night for 'magical' effects.",
        "Has an irrational fear of even numbers and avoids them whenever possible.",
    ]
    quirk = random.choice(quirks)
    quirkStr.set("Quirk: " + quirk)


def main():
    # Root
    root = Tk()

    # Adjust size
    width = root.winfo_screenwidth()
    height = root.winfo_screenheight()
    root.geometry("%dx%d" % (width, height))

    defaultFont = font.nametofont("TkDefaultFont")
    defaultFont.configure(family = "Roman", size = 14)

    # Title
    root.title("Dungeons and Dragons NPC Generator")

    # Color
    root.config(background = "#e1d8b9")

    # Title
    title = ttk.Label(root, text = "Dungeons and Dragons NPC Generator", background = "#e1d8b9")
    title.config(justify = CENTER)
    title.config(padding = 15)
    title.pack()

    frameBind = ttk.Frame(root)
    frameBind.config(width = 800, height = 800)

    # Physical Features Frame
    physFrame = ttk.Frame(frameBind)
    physFrame.config(relief = RIDGE, width = 400, height = 400)

    # Physical Features Label
    physFt = ttk.Label(physFrame, text = "Physical Features")
    physFt.config(justify = CENTER)
    physFt.config(padding = 15)
    physFt.grid(row = 0, column = 0, columnspan = 2)  

    # Race
    raceStr = StringVar(physFrame, "Race: ")
    raceLabel = ttk.Label(physFrame, textvariable = raceStr)
    raceLabel.config(justify = CENTER)
    raceLabel.config(padding = 15)
    raceLabel.grid(row = 1, column = 0)

    # Age
    ageStr = StringVar(physFrame, "Age: ")
    ageLabel = ttk.Label(physFrame, textvariable = ageStr)
    ageLabel.config(justify = CENTER)
    ageLabel.config(padding = 15)
    ageLabel.grid(row = 1, column = 1)
    
    # Height
    heightStr = StringVar(physFrame, "Height: ")
    heightLabel = ttk.Label(physFrame, textvariable = heightStr)
    heightLabel.config(justify = CENTER)
    heightLabel.config(padding = 15)
    heightLabel.grid(row = 2, column = 0)

    # Hair
    hairStr = StringVar(physFrame, "Hair: ")
    hairLabel = ttk.Label(physFrame, textvariable = hairStr)
    hairLabel.config(justify = CENTER)
    hairLabel.config(padding = 15)
    hairLabel.grid(row = 2, column = 1)

    # Eyes
    eyesStr = StringVar(physFrame, "Eyes: ")
    eyesLabel = ttk.Label(physFrame, textvariable = eyesStr)
    eyesLabel.config(justify = CENTER)
    eyesLabel.config(padding = 15)
    eyesLabel.grid(row = 3, column = 0)

    # Build
    buildStr = StringVar(physFrame, "Build: ")
    buildLabel = ttk.Label(physFrame, textvariable = buildStr)
    buildLabel.config(justify = CENTER)
    buildLabel.config(padding = 15)
    buildLabel.grid(row = 3, column = 1)

    # Fashion Description
    fashionStr = StringVar(physFrame, "Style: ")
    fashionLabel = ttk.Label(physFrame, textvariable = fashionStr)
    fashionLabel.config(justify = CENTER)
    fashionLabel.config(wraplength = 250)
    fashionLabel.config(padding = 15)
    fashionLabel.grid(row = 4, column = 0, columnspan = 2)

    # Pack Physical Frame
    physFrame.config(padding = 50)
    physFrame.pack(side = LEFT, anchor = CENTER, fill = BOTH)

    # Character Features Frame
    charFrame = ttk.Frame(frameBind)
    charFrame.config(relief = RIDGE, width = 400, height = 400)

    # Character Features Label
    charFt = ttk.Label(charFrame, text = "Character Features")
    charFt.config(justify = CENTER)
    charFt.config(padding = 15)
    charFt.grid(row = 0, column = 0, columnspan = 2)    

    # First Name
    firstStr = StringVar(charFrame, "First: ")
    firstLabel = ttk.Label(charFrame, textvariable = firstStr)
    firstLabel.config(justify = CENTER)
    firstLabel.config(padding = 15)
    firstLabel.grid(row = 1, column = 0)

    # Last Name
    lastStr = StringVar(charFrame, "Last: ")
    lastLabel = ttk.Label(charFrame, textvariable = lastStr)
    lastLabel.config(justify = CENTER)
    lastLabel.config(padding = 15)
    lastLabel.grid(row = 1, column = 1)
    
    # Class
    classStr = StringVar(charFrame, "Class: ")
    clasLabel = ttk.Label(charFrame, textvariable = classStr)
    clasLabel.config(justify = CENTER)
    clasLabel.config(padding = 15)
    clasLabel.config(wraplength = 125)
    clasLabel.grid(row = 2, column = 0)

    # Gender
    gStr = StringVar(charFrame, "Gender: ")
    gLabel = ttk.Label(charFrame, textvariable = gStr)
    gLabel.config(justify = CENTER)
    gLabel.config(padding = 15)
    gLabel.grid(row = 2, column = 1)

    # Level
    lvlStr = StringVar(charFrame, "Level: ")
    lvlLabel = ttk.Label(charFrame, textvariable = lvlStr)
    lvlLabel.config(justify = CENTER)
    lvlLabel.config(padding = 15)
    lvlLabel.grid(row = 3, column = 0)

    # Alignment
    algnStr = StringVar(charFrame, "Alignment: ")
    algnLabel = ttk.Label(charFrame, textvariable = algnStr)
    algnLabel.config(justify = CENTER)
    algnLabel.config(padding = 15)
    algnLabel.config(wraplength = 125)
    algnLabel.grid(row = 3, column = 1)

    # Quirk
    quirkStr = StringVar(charFrame, "Quirk: ")
    quirkLabel = ttk.Label(charFrame, textvariable = quirkStr)
    quirkLabel.config(justify = CENTER)
    quirkLabel.config(wraplength = 250)
    quirkLabel.config(padding = 15)
    quirkLabel.grid(row = 4, column = 0, columnspan = 2)

    # Pack Character Frame
    charFrame.config(padding = 50)
    charFrame.pack(side = RIGHT, anchor = CENTER, fill = BOTH)

    frameBind.pack()

    # Generate Button
    button = ttk.Button(root, text = 'Click to Generate your NPC!', command = lambda: generate(raceStr, ageStr, heightStr, hairStr, eyesStr, buildStr, fashionStr, firstStr, lastStr, classStr, gStr, lvlStr, algnStr, quirkStr))
    button.config(padding = 5)
    button.pack(side = BOTTOM, pady = 50)
    root.mainloop()


main()
