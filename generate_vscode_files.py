from pathlib import Path
import shutil

CURRENT = Path(__file__).resolve().parent
ConfPath = CURRENT / ".vscode"
if ConfPath.exists():
    shutil.rmtree(ConfPath)

ConfPath.mkdir()
tasks_conf = ConfPath / "tasks.json"

if False:
    tasks_conf.write_text(
    """
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": ["pwsh", "build.ps1"]
        }
    ]
}"""
)
build_dir = list(CURRENT.glob("build-qt_stub*"))
if len(build_dir) != 1:
    print("error: mutiple build path")
    exit(-1)

build_dir = build_dir[0]
import glob

built_exes = list(glob.glob("**/*.exe", root_dir=build_dir, recursive=True))

conf_single = """
        {
            "name": "{progname}",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/{dirname}/{program}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ]
        }"""

dirname = build_dir.name
conf_single = conf_single.replace("{dirname}", dirname)

confs = []
for built_exe in built_exes:
    built_exe = built_exe.replace("\\", "/")
    prog_name = Path(built_exe).resolve().name
    conf = conf_single.replace("{program}", built_exe).replace("{progname}", prog_name)
    confs.append(conf)

confs_str = ",".join(confs)

launch_conf = ConfPath / "launch.json"

launch_conf.write_text(
    """{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [{confs_str}
    ]
}""".replace(
        "{confs_str}", confs_str
    )
)
