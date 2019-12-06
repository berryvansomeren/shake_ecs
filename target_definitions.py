from pathlib import Path
from typing import List

from cmake_generator import NewTarget, Target, TargetType

# ----------------------------------------------------------------
def get_target_definitions() -> List[ Target ] :
    shake_ecs = NewTarget(
        name = 'shake_ecs',
        target_type = TargetType.SharedLibrary,
        src_dir_path = ( Path( __file__ ).resolve().parent / 'src/' ).as_posix(),
        dependencies = [
            'glm',
            'pybind11',
            'shake_core',
            'shake_graphics',
            'shake_hid'
        ]
    )
    return [ shake_ecs ]
