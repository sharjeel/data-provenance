/*
--------------------------------------------------------------------------------
SPADE - Support for Provenance Auditing in Distributed Environments.
Copyright (C) 2011 SRI International

This program is free software: you can redistribute it and/or  
modify it under the terms of the GNU General Public License as  
published by the Free Software Foundation, either version 3 of the  
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,  
but WITHOUT ANY WARRANTY; without even the implied warranty of  
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  
General Public License for more details.

You should have received a copy of the GNU General Public License  
along with this program. If not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------------------
 */
package spade.opm.vertex;

import spade.core.AbstractVertex;
import java.util.Map;
import java.util.LinkedHashMap;

/**
 * Agent vertex based on the OPM model
 * 
 * @author Dawood
 */
public class Agent extends AbstractVertex {

    /**
     * Constructor for this vertex that takes a map of annotations.
     * 
     * @param inputAnnotations The map of annotations to be set for this vertex.
     */
    public Agent(Map<String, String> inputAnnotations) {
        this.setAnnotations(inputAnnotations);
        this.addAnnotation("type", "Agent");
    }

    /**
     * Empty constructor - initializes an empty map for annotations.
     */
    public Agent() {
        this.setAnnotations(new LinkedHashMap<String, String>());
        this.addAnnotation("type", "Agent");
    }
}
