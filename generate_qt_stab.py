from pathlib import Path
import shutil

CURRENT = Path(__file__).resolve().parent

files = list(CURRENT.glob("*.cpp"))
files.extend(list(CURRENT.glob("*.cc")))

QtStabPath = Path("qt_stab")
if QtStabPath.exists():
    shutil.rmtree(QtStabPath)
QtStabPath.mkdir()

for file in files:
    libs = []
    with open(file, "r") as f:
        line = f.readline()
        if "link=" in line:
            parts = line.replace("//", "").split("link=")
            if len(parts) > 1:
                libs = parts[1].split()
    libs_str = " ".join(map(lambda x: f"-l{x}", libs))
    folder_name = file.stem
    dir_name = QtStabPath / folder_name
    dir_name.mkdir(exist_ok=True)
    pro_name = dir_name / f"{folder_name}.pro"
    if not pro_name.exists():
        with open(pro_name, mode="w") as f:
            f.write(
                f"""
TEMPLATE = app
CONFIG -= qt app_bundle
CONFIG += console c++17

SOURCES += ../../{file.name}
"""
            )
            if len(libs) != 0:
                f.write(
                    f"""
LIBS += {libs_str}
"""
                )

qt_stab_pro = QtStabPath / "qt_stab.pro"
subdirs = " ".join(map(lambda x: x.stem, files))
if not qt_stab_pro.exists():
    with open(qt_stab_pro, "w") as f:
        f.write(
            f"""
TEMPLATE = subdirs
SUBDIRS += {subdirs}
"""
        )
