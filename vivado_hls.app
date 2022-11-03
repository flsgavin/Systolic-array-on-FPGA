<project xmlns="com.autoesl.autopilot.project" name="testTPU" top="matrix_mult">
    <files>
        <file name="testTPU/src/im2col.cpp" sc="0" tb="false" cflags=""/>
        <file name="testTPU/src/im2col.h" sc="0" tb="false" cflags=""/>
        <file name="testTPU/src/instr.cpp" sc="0" tb="false" cflags=""/>
        <file name="testTPU/src/instr.h" sc="0" tb="false" cflags=""/>
        <file name="testTPU/src/sa.cpp" sc="0" tb="false" cflags=""/>
        <file name="testTPU/src/sa.h" sc="0" tb="false" cflags=""/>
        <file name="../feature.dat" sc="0" tb="1" cflags=""/>
        <file name="../src/tb_mxu.cpp" sc="0" tb="1" cflags=""/>
        <file name="../weight.dat" sc="0" tb="1" cflags=""/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" optimizeCompile="true" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

