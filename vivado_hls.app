<project xmlns="com.autoesl.autopilot.project" name="testTPU" top="im2col">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" optimizeCompile="true" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <files xmlns="">
        <file name="../weight.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="../src/tb_mxu.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="../feature.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="testTPU/src/sa.h" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="testTPU/src/sa.cpp" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="testTPU/src/instr.h" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="testTPU/src/instr.cpp" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="testTPU/src/im2col.h" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="testTPU/src/im2col.cpp" sc="0" tb="false" cflags="" blackbox="false"/>
    </files>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

