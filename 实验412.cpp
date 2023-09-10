fprintf(outputFile, "比较次数表\tA1\tA2\tA3\tA4\n");
    fprintf(outputFile, "        S1\t%d\t%d\t%d\t%d\n", compareCountS1A1, compareCountS1A2, compareCountS1A3, compareCountS1A4);
    fprintf(outputFile, "        S2\t%d\t%d\t%d\t%d\n", compareCountS2A1, compareCountS2A2, compareCountS2A3, compareCountS2A4);
    fprintf(outputFile, "        S3\t%d\t%d\t%d\t%d\n", compareCountS3A1, compareCountS3A2, compareCountS3A3, compareCountS3A4);
    fprintf(outputFile, "        S4\t%d\t%d\t%d\t%d\n", compareCountS4A1, compareCountS4A2, compareCountS4A3, compareCountS4A4);

    fprintf(outputFile, "移动次数表\tA1\tA2\tA3\tA4\n");
	fprintf(outputFile, "        S1\t%d\t%d\t%d\t%d\n", moveCountS1A1, moveCountS1A2, moveCountS1A3, moveCountS1A4);
	fprintf(outputFile, "        S2\t%d\t%d\t%d\t%d\n", moveCountS2A1, moveCountS2A2, moveCountS2A3, moveCountS2A4);
	fprintf(outputFile, "        S3\t%d\t%d\t%d\t%d\n", moveCountS3A1, moveCountS3A2, moveCountS3A3, moveCountS3A4);
	fprintf(outputFile, "        S4\t%d\t%d\t%d\t%d\n", moveCountS4A1, moveCountS4A2, moveCountS4A3, moveCountS4A4);
    
    fprintf(outputFile, "执行时间表\tA1\tA2\tA3\tA4\n");
	fprintf(outputFile, "        S1\t%ld\t%ld\t%ld\t%ld\n", executionTimeS1A1, executionTimeS1A2, executionTimeS1A3, executionTimeS1A4);
	fprintf(outputFile, "        S2\t%ld\t%ld\t%ld\t%ld\n", executionTimeS2A1, executionTimeS2A2, executionTimeS2A3, executionTimeS2A4);
	fprintf(outputFile, "        S3\t%ld\t%ld\t%ld\t%ld\n", executionTimeS3A1, executionTimeS3A2, executionTimeS3A3, executionTimeS3A4);
	fprintf(outputFile, "        S4\t%ld\t%ld\t%ld\t%ld\n", executionTimeS4A1, executionTimeS4A2, executionTimeS4A3, executionTimeS4A4); 
